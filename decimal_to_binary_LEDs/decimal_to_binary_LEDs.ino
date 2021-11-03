/*
 * Written by Nathan Rolfes
 */

//if you want to print out 0 to 2^BITVALUE in binary using LEDs
const int BITVALUE = 6;

//plug LEDs into these pins on arduino
//represents 2^(BITVALUE - 1), 2^(BITVALUE - 2), .... , 2, 1
int ledArray[BITVALUE] = {12, 11, 10, 9, 8, 7};

//function converts a decimal value to its binary value and stores
//the 0s and 1s in an array
int* decimal_to_binary_array(int decimalValue, int bitValue) {
  static int binary[BITVALUE];
  
  //this loop will assign each value of binary array a 0 or 1
  for (int j = bitValue - 1; j >= 0; j--) {  
    int integerRepresentation = bit(j);   

    //for example, if 15>8, binary digit that represents 8 is 
    //moved to 1 and 15 is subtracted by 8. The same process is 
    //then done with 7>4 for next loop iteration
    if (decimalValue >= integerRepresentation) {            
      binary[bitValue - j - 1] = 1;
      decimalValue -= integerRepresentation;
    } else {
      binary[bitValue - j - 1] = 0;
    }
  }
  
  return binary;
}


void setup() {
  Serial.begin(9600);
  
  for (int i = 0; i < BITVALUE; i++) {
    pinMode(ledArray[i], OUTPUT);
  }
}


void loop() {
  //by default, write LED's to low at the start of each count
  for (int i = 0; i < BITVALUE; i++) {
    digitalWrite(ledArray[i], LOW);
  }
  
  //for each digit that you want to print in binary (2^BITVALUE)
  for (int i = 0; i < bit(BITVALUE); i++) {
    int *binary;
  
    //binary is an array with size of BITVALUE, containing 0s and 1s
    binary = decimal_to_binary_array(i, BITVALUE);
  
    //for each element in binary array, set LED to high if 1 and low if 0
    for (int k = 0; k < BITVALUE; k++) {
      if (*(binary + k) == 1) {
        digitalWrite(ledArray[k], HIGH);
      }
      else {
        digitalWrite(ledArray[k], LOW);
      }
    }
  
    //prints, for each integer, binary representation, then decimal, like so:
    //0 0 0 0 0 
    //0 0 0 1 1 
    //0 0 1 0 2
    //0 0 1 1 3 
    for (int k = 0; k < BITVALUE; k++) {
      Serial.print(*(binary+k));
      Serial.print(' ');
    }
    Serial.print(String(i));
    Serial.println(' ');
  
    //0.5 secs inbetween each number
    delay(500);
  }
  
  for (int i = 0; i < BITVALUE; i++) {
    digitalWrite(ledArray[i], LOW);
  }
}
