#include <FastLED.h>
#define LED_PIN     2
#define NUM_LEDS    30
CRGB leds[NUM_LEDS];
//RGB LEDLights

#include <Arduino.h>

#define trigPin 12
#define echoPin 13
//Define the Trig port of the ultrasonic sensor connected to Pin12 
//The Echo port connected to Pin13

float cm;
float temp;
//define Ultrasonic sensor

#include <Servo.h>
Servo myservo;//Define Servo objects to control
int pos = 0;//Angle storage variable
int pos_add =-180;

const int sensorPin = A0;
int sensorValue = 0;
//Touch Sensor

//The last LED flashing time will be stored
//The period of blinking in milliseconds
const long interval_motor = 100; 
const long interval_light = 500;
unsigned long previousMillis_motor;
unsigned long previousMillis_motor2 = 0;
unsigned long previousMillis_light = 0; 

float sinVal;
int toneVal;
//Define a buzzer



void setup() {
  Serial.begin(9600);

  myservo.attach(10);
  //Connect the steering gear (servo) to Pin10

  //Define the pin state of the ultrasonic sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  pinMode(8, OUTPUT);
  
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
}
void loop() {
  // Touch sensor control motor
  unsigned long currentMillis = millis();
  //static unsigned long  motor_timestamp = millis();

    // myservo.write(0);
  

    //Serial.println(time_now);


  sensorValue = analogRead(sensorPin);
  //delayMicroseconds(10);
  Serial.println(sensorValue);


  if (sensorValue <= 10){
    
    //digitalWrite(10, HIGH);
    //delayMicroseconds(500);

   
  if (currentMillis - previousMillis_motor >= interval_motor){

    //time_now2 = millis();
    previousMillis_motor = currentMillis;
    //motor_state1();

    
    pos += pos_add;
    
    myservo.write(-pos);

    //if ((pos >= 0) || (pos <= 180)){
    //
    if ((pos >= 180) || (pos <= 0)){
      pos_add = -pos_add;
    }
  }

  }

 /*   
if (currentMillis - previousMillis_motor >= interval_motor){
  previousMillis_motor = currentMillis;
    
}*/

unsigned long currentMillis_light = millis();

// Ultrasonic sensor
// Trigger the ultrasonic sensor
// Send a short low and low pulse to the Trig to trigger the ranging

  digitalWrite(trigPin, LOW); //Send a low level to Trig
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); //Send a high level to Trig
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW); //Send a low level to Trig
  
  temp = float(pulseIn(echoPin,HIGH));
  //Calculate the time for this echoPin to change from high to low level
  // Store echo wait time,
  //The pulseIn function waits for the pin to change to HIGH, starts calculating the time, and then waits for the pin to change to LOW and stops the time
  // The length of the return pulse

  // Sound speed :340m/1s converted to 34000cm / 1000000μs => 34/1000
  // Because sending to receiving actually travels the same distance twice, divide by 2
  // Distance (cm) = (echo time * (34/1000)) / 2
  // The simplified calculation formula is (echo time * 17)/ 1000
  
if (currentMillis_light - previousMillis_light >= 50){
  previousMillis_light = currentMillis_light;
  cm = (temp * 17)/1000;
  // Convert the echo time to cm

 // Serial.print("Distance:");
 // Serial.print(cm);
 // Serial.println(" cm");
//  delay(50);
}


    if (cm >30){
  //If the ultrasonic sensor detects a person more than 30cm away, it emits a red to white flashing light
  // Red
  for (int i = 0; i <= 12; i++) {
    leds[i] = CRGB ( 255, 0, 0);
    FastLED.show();
    delay(40);
    
  }for (int i = 0; i <= 12; i++) {
    //leds[i] = CRGB ( 255, 255, 255);
    leds[i] = CRGB ( 255,20,147);
    FastLED.show();
    delay(40);
    
  }
   
    }
    
  // Green
   else if(cm<30){
  //If the ultrasonic sensor detects a person less than 30cm away, it emits a green to blue flashing light
  // if (currentMillis_light - previousMillis_light >=10){
  //previousMillis_light = currentMillis_light;
  for (int i = 0; i <= 12; i++) {
    leds[i] = CRGB ( 0, 255, 0);
    FastLED.show();
    delay(40);
     //}
     }

     //  Blue
  for (int i = 0; i <= 12; i++) {
    leds[i] = CRGB ( 0, 0, 255);
    FastLED.show();
    delay(40);
  }
   }
 /* */
/*

//蜂鸣器
//for(int f=0; f<180; f++){
            //将sin函数角度转化为弧度
           // sinVal = (sin(f*(cm)));
            //sinVal = (cm+sin(f*(3.1412/180)));
            sinVal = cm*10;
            //用sin函数值产生声音的频率
            //toneVal = 1000+(int(sinVal*1000));
            //给引脚8一个
            toneVal = 1000+(int(sinVal*2000));
            tone(8, toneVal);
            //toneVal = 1000+(int(sinVal*1000))
            delay(2); 
    // }   */

     for(int x=0; x<180; x++){
            //将sin函数角度转化为弧度
            //sinVal = (sin(x*(3.1412/180)));
            sinVal = (sin(x*(3.1412/180)));
            //用sin函数值产生声音的频率
           // toneVal = cm +(int(sinVal*1000));
           toneVal = sensorValue +(int(sinVal*1000));
            //给引脚8一个
            tone(8, toneVal);
            delay(1); 
     }   
}
