// Library untuk mengontrol register shift
#include <SPI.h>
const int dataPin = 2;   // Pin DS pada SN74HC595N
const int clockPin = 4;  // Pin SH_CP pada SN74HC595N
const int latchPin = 5;  // Pin ST_CP pada SN74HC595N
// Jumlah LED yang akan dikendalikan
const int jumlahLED = 8;
void setup() {
  // Set pin mode untuk pin yang digunakan
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {
  // Penyalakan 8 LED maju 3x
  for (int loopCount = 0; loopCount < 3; loopCount++) {
    for (int i = 0; i < 8; i++) {
      shiftOut(dataPin, clockPin, MSBFIRST, 1 << i);
      digitalWrite(latchPin, HIGH);
      delay(100);
      digitalWrite(latchPin, LOW);
    }

    // Matikan semua LED
    updateShiftRegister(0);
    delay(500);
  }

  // Penyalakan 8 LED mundur 3x
  for (int j = 0; j < 3; j++) {
    for (int i = 7; i >= 0; i--) {
      shiftOut(dataPin, clockPin, MSBFIRST, 1 << i);
      digitalWrite(latchPin, HIGH);
      delay(100);
      digitalWrite(latchPin, LOW);
    }
    updateShiftRegister(0);
    delay(500);
  }

  // Nyala semua 3 kali
  for (int k = 0; k < 3; k++) {
    updateShiftRegister(255);  // 255 untuk menyalakan semua LED
    delay(50);
    updateShiftRegister(0);
    delay(500);
  }

// Nyala 4 LED kanan dan 4 LED kiri secara bergantian
  for (int m = 0; m < 6; m++) {
    for (int i = 0; i < 4; i++) {
      updateShiftRegister(1 << i | 1 << (7 - i));
      delay(50);
    }
    updateShiftRegister(0);
    delay(100); // Delay tambahan setelah Nyala 4 LED kanan dan 4 LED kiri secara bergantian

    // Nyala 4 LED kanan dan 4 LED kiri secara bergantian dan sebaliknya
    for (int i = 3; i >= 0; i--) {
      updateShiftRegister(1 << i | 1 << (7 - i));
      delay(50);
    }
    updateShiftRegister(0);
    delay(100); // Delay tambahan setelah Nyala 4 LED kanan dan 4 LED kiri secara bergantian dan sebaliknya
  }


  // Berjalan maju mundur setelah Nyala 4 LED kanan dan 4 LED kiri secara bergantian delay 100
  for (int n = 0; n < 3; n++) {
    // Berjalan maju
    for (int i = 0; i < 8; i++) {
      shiftOut(dataPin, clockPin, MSBFIRST, 1 << i);
      digitalWrite(latchPin, HIGH);
      delay(100);
      digitalWrite(latchPin, LOW);
    }

    // Berjalan mundur
    for (int i = 7; i >= 0; i--) {
      shiftOut(dataPin, clockPin, MSBFIRST, 1 << i);
      digitalWrite(latchPin, HIGH);
      delay(100);
      digitalWrite(latchPin, LOW);
    }
  }

  // Nyala semua
  updateShiftRegister(255);
  delay(1000);

  // Matikan semua LED
  updateShiftRegister(0);
  delay(500);
}

void updateShiftRegister(byte data) {
  shiftOut(dataPin, clockPin, MSBFIRST, data);
  digitalWrite(latchPin, HIGH);
  delay(100);
  digitalWrite(latchPin, LOW);
}