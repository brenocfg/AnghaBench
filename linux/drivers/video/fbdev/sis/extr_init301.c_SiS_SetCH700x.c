#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct SiS_Private {int SiS_DDC_DeviceAddr; int SiS_DDC_Index; int SiS_DDC_Data; int SiS_DDC_Clk; int /*<<< orphan*/  SiS_ChrontelInit; } ;

/* Variables and functions */
 int /*<<< orphan*/  SiS_DDC2Delay (struct SiS_Private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SiS_I2CDELAYSHORT ; 
 int /*<<< orphan*/  SiS_SetChReg (struct SiS_Private*,unsigned short,unsigned char,int) ; 
 int /*<<< orphan*/  SiS_SetupDDCN (struct SiS_Private*) ; 

void
SiS_SetCH700x(struct SiS_Private *SiS_Pr, unsigned short reg, unsigned char val)
{
  SiS_Pr->SiS_DDC_DeviceAddr = 0xEA;  		/* DAB (Device Address Byte) */

  SiS_DDC2Delay(SiS_Pr,SiS_I2CDELAYSHORT);

  if(!(SiS_Pr->SiS_ChrontelInit)) {
     SiS_Pr->SiS_DDC_Index = 0x11;		/* Bit 0 = SC;  Bit 1 = SD */
     SiS_Pr->SiS_DDC_Data  = 0x02;		/* Bitmask in IndexReg for Data */
     SiS_Pr->SiS_DDC_Clk   = 0x01;		/* Bitmask in IndexReg for Clk */
     SiS_SetupDDCN(SiS_Pr);
  }

  if( (!(SiS_SetChReg(SiS_Pr, reg, val, 0x80))) &&
      (!(SiS_Pr->SiS_ChrontelInit)) ) {
     SiS_Pr->SiS_DDC_Index = 0x0a;
     SiS_Pr->SiS_DDC_Data  = 0x80;
     SiS_Pr->SiS_DDC_Clk   = 0x40;
     SiS_SetupDDCN(SiS_Pr);

     SiS_SetChReg(SiS_Pr, reg, val, 0x80);
  }
}