#define sr_column 2
#define sl_column 3
#define mr_column 4
#define ml_column 5
#define hr_column 6
#define hl_column 7
#define row1 13
#define row2 12
#define row3 11
#define row4 10

unsigned h = 0;
unsigned m = 0;
unsigned s = 0;

unsigned long lastMillis = 0UL;

void setup()
{
  Serial.begin(9600);
  
  pinMode(sr_column, OUTPUT);
  pinMode(sl_column, OUTPUT);
  pinMode(mr_column, OUTPUT);
  pinMode(ml_column, OUTPUT);
  pinMode(hr_column, OUTPUT);
  pinMode(hl_column, OUTPUT);
  pinMode(row1,  OUTPUT);
  pinMode(row2,  OUTPUT);
  pinMode(row3,  OUTPUT);
  pinMode(row4,  OUTPUT);
}

void decimalToBinary(unsigned dec, unsigned *target_array)
{
  unsigned index = 0;
  
  if(dec > 9)
    dec = 9;
  
  while (dec > 0)
  {
    target_array[index++] = dec % 2;
    dec = dec / 2;
  }
}

void displayColumn(unsigned column, unsigned *bin_array)
{
  digitalWrite(column, HIGH);

  for(int i = 0; i < 4; i++)
    digitalWrite(row4 + i, bin_array[i]);

  delay(2);
  digitalWrite(column, LOW);
}

void displayValues(unsigned l_column, unsigned r_column, unsigned value)
{
  unsigned tens = value / 10;
  unsigned ones = value - (tens * 10);

  unsigned tens_binary[4] = {0,0,0,0};
  unsigned ones_binary[4] = {0,0,0,0};

  decimalToBinary(tens, tens_binary);
  decimalToBinary(ones, ones_binary);

  displayColumn(l_column, tens_binary);
  displayColumn(r_column, ones_binary);
}

void loop()
{
  unsigned long currentMillis = millis();
  
  if(currentMillis - lastMillis > 1000)
  {
    s++;
    
    if(s >= 60)
    {
      m++;
      s = 0;
      
      if(m >= 60)
      {
        h++;
        m = 0;
        if(h >= 24)
          h = 0;
      }
    }
    
    lastMillis = currentMillis;
  }
  
  displayValues(sl_column, sr_column, s);
  displayValues(ml_column, mr_column, m);
  displayValues(hl_column, hr_column, h);
}