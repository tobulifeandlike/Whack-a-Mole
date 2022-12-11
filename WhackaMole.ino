//Variables for Setup 
int molepin;
int hammerpin;
long regulatedTime;
long countTime;
long cumulatedTime = 0;

//Variables for Logic Judgement
int judgehammer;
boolean hit;
const int hammer1 = 0; const int hammer2 = 1; const int hammer3 = 2; 
const int hammer4 = 3; const int hammer5 = 4; const int hammer6 = 5;

const int mole1 = 6; const int mole2 = 7; const int mole3 = 8;
const int mole4 = 9; const int mole5 = 10; const int mole6 = 11;

const int indicatorNo = 12;
const int indicatorYes = 13;

void setup() {
  Initialization();
}

void loop() {
  // put your main code here, to run repeatedly:
  //1. Total game time, mole out time setup
  cumulatedTime = millis();
  countTime = RegulatecountTime(cumulatedTime);
  regulatedTime = OutTimeLast(countTime);

  //2. Randomly generate a mole  
  molepin = MoleOut();

  //3. Check if the mole is hit in the regulatedTime
  cumulatedTime = millis();
  hit = HammerPress(molepin,regulatedTime,cumulatedTime);

  //4. Judge the hit condition
  if (hit==true){
    digitalWrite(molepin,LOW);
    digitalWrite(indicatorYes,HIGH);
    delay(500);
    digitalWrite(indicatorYes,LOW);
  }
  else {
    delay(regulatedTime);
    MoleIn(molepin);
    digitalWrite(indicatorNo,HIGH);
    delay(500);
    digitalWrite(indicatorNo,LOW);
  }
  
}

void Initialization(){
  //Set pinMode of every mole pin and every hammer pin
  //All mole pins output the digital signal to control the 
  //corresponding LED
  pinMode(mole1,OUTPUT);pinMode(mole2,OUTPUT);pinMode(mole3,OUTPUT);
  pinMode(mole4,OUTPUT);pinMode(mole5,OUTPUT);pinMode(mole6,OUTPUT);
  //Two Indicator Pins Control the LEDs to indicate if the player correctly hits the mole in regulated time 
  pinMode(indicatorNo,OUTPUT);
  pinMode(indicatorYes,OUTPUT);
  //All hammer pins get the signal from the pushbutton-resistor circuit
  //voltage signal to change the state of corresponding mole LED
  pinMode(hammer1,INPUT);pinMode(hammer2,INPUT);pinMode(hammer3,INPUT);
  pinMode(hammer4,INPUT);pinMode(hammer5,INPUT);pinMode(hammer6,INPUT);
}

int MoleOut(){
  //Randomly generate a mole out of the cave(LED on) 
  int molepin = random(mole1,mole6);
  digitalWrite(molepin,HIGH);
  delay(regulatedTime);
  return molepin;
}

void MoleIn(int molepin){
  //Mole gets back to the cave(LED off)
  digitalWrite(molepin,LOW);
}

//Modify the mole out time in this function
//Change the regulatedTime
long OutTimeLast(long countTime){
  if(countTime<=40000){
    regulatedTime = 1000;
  }
  else if(countTime<=120000){
    regulatedTime = 850;
  }
  else if(countTime<=180000){
    regulatedTime = 650;
  }
  return regulatedTime;
}

boolean HammerPress(int molepin, long regulatedTime,long cumulatedTime){
  //Judge if the corresponding hammer key is pressed
  judgehammer = map(molepin, mole1, mole6, hammer1, hammer6);
  long shortcountTime = millis()-cumulatedTime;
  hit = false; boolean originalstate = LOW;
  if ((digitalRead(judgehammer)!=originalstate)&&(shortcountTime<=regulatedTime)){
    shortcountTime = millis()-cumulatedTime;
    originalstate = HIGH;
    if (digitalRead(judgehammer)!=originalstate){
      shortcountTime = millis()-cumulatedTime;
      if ((digitalRead(judgehammer)==originalstate)&&(shortcountTime<=regulatedTime)){
        hit = true;
      }
    }
    else if ((digitalRead(judgehammer)==originalstate)&&(shortcountTime<=regulatedTime)){
        hit = true;
      }
  }
  return hit;
}

long RegulatecountTime(long cumulatedTime){
  //The game resets every three minutes
  countTime = millis();
  if (cumulatedTime>=180000){
    countTime = millis()-cumulatedTime;
  }
  return countTime;
}
