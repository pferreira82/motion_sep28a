//Callabrate motion sensor
int calibrationTime = 15;        

//The time when the sensor outputs a low impulse
long unsigned int lowIn;         

//The amount of milliseconds the sensor has to be low 
//Before we assume all motion has stopped
long unsigned int pause = 5000;  

boolean lockLow = true;
boolean takeLowTime;  

int pirPin = 3;    //Motion sensor pin
int relayPin = 13;  // Relay pin


void setup(){
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  pinMode(relayPin, OUTPUT);
  digitalWrite(pirPin, LOW);

  Serial.print("calibrating sensor ");
    for(int i = 0; i < calibrationTime; i++){
      Serial.print(".");
      delay(1000);
      }
    Serial.println(" done");
    Serial.println("SENSOR ACTIVE!!!");
    delay(50);
  }


void loop(){

     if(digitalRead(pirPin) == HIGH){
       digitalWrite(relayPin, LOW);   
       if(lockLow){  
         lockLow = false;            
         Serial.println("---");
         Serial.print("motion detected at ");
         Serial.print(millis()/1000);
         Serial.println(" sec"); 
         delay(50);
         }         
         takeLowTime = true;
       }

     if(digitalRead(pirPin) == LOW){       
       digitalWrite(relayPin, HIGH);  

       if(takeLowTime){
        lowIn = millis();          //save the time of the transition from high to LOW
        takeLowTime = false;       
        }
       //Motion pause
       if(!lockLow && millis() - lowIn > pause){
           lockLow = true;                        
           Serial.print("motion ended at ");      
           Serial.print((millis() - pause)/1000);
           Serial.println(" sec");
           delay(50);
           }
       }
  }

