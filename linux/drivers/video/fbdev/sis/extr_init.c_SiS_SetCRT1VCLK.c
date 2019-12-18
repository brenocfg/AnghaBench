#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct SiS_Private {unsigned short CSR2B; unsigned short CSR2C; int SiS_VBType; int SiS_VBInfo; scalar_t__ ChipType; int /*<<< orphan*/  SiS_P3c4; TYPE_2__* SiS_VCLKData; TYPE_1__* SiS_VBVCLKData; scalar_t__ Alternate1600x1200; scalar_t__ UseCustomMode; } ;
struct TYPE_4__ {unsigned short SR2B; unsigned short SR2C; } ;
struct TYPE_3__ {unsigned short Part4_A; unsigned short Part4_B; } ;

/* Variables and functions */
 unsigned short HalfDCLK ; 
 scalar_t__ SIS_315H ; 
 int SetCRT2ToLCDA ; 
 unsigned short SiS_GetModeFlag (struct SiS_Private*,unsigned short,unsigned short) ; 
 int SiS_GetReg (int /*<<< orphan*/ ,int) ; 
 unsigned short SiS_GetVCLK2Ptr (struct SiS_Private*,unsigned short,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetReg (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SiS_SetRegAND (int /*<<< orphan*/ ,int,int) ; 
 int VB_SIS30xBLV ; 
 scalar_t__ XGI_20 ; 

__attribute__((used)) static void
SiS_SetCRT1VCLK(struct SiS_Private *SiS_Pr, unsigned short ModeNo,
		unsigned short ModeIdIndex, unsigned short RRTI)
{
   unsigned short index = 0, clka, clkb;

   if(SiS_Pr->UseCustomMode) {
      clka = SiS_Pr->CSR2B;
      clkb = SiS_Pr->CSR2C;
   } else {
      index = SiS_GetVCLK2Ptr(SiS_Pr, ModeNo, ModeIdIndex, RRTI);
      if((SiS_Pr->SiS_VBType & VB_SIS30xBLV) &&
	 (SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA)) {
	 /* Alternate for 1600x1200 LCDA */
	 if((index == 0x21) && (SiS_Pr->Alternate1600x1200)) index = 0x72;
	 clka = SiS_Pr->SiS_VBVCLKData[index].Part4_A;
	 clkb = SiS_Pr->SiS_VBVCLKData[index].Part4_B;
      } else {
	 clka = SiS_Pr->SiS_VCLKData[index].SR2B;
	 clkb = SiS_Pr->SiS_VCLKData[index].SR2C;
      }
   }

   SiS_SetRegAND(SiS_Pr->SiS_P3c4,0x31,0xCF);

   SiS_SetReg(SiS_Pr->SiS_P3c4,0x2b,clka);
   SiS_SetReg(SiS_Pr->SiS_P3c4,0x2c,clkb);

   if(SiS_Pr->ChipType >= SIS_315H) {
#ifdef CONFIG_FB_SIS_315
      SiS_SetReg(SiS_Pr->SiS_P3c4,0x2D,0x01);
      if(SiS_Pr->ChipType == XGI_20) {
         unsigned short mf = SiS_GetModeFlag(SiS_Pr, ModeNo, ModeIdIndex);
	 if(mf & HalfDCLK) {
	    SiS_SetReg(SiS_Pr->SiS_P3c4,0x2b,SiS_GetReg(SiS_Pr->SiS_P3c4,0x2b));
	    clkb = SiS_GetReg(SiS_Pr->SiS_P3c4,0x2c);
	    clkb = (((clkb & 0x1f) << 1) + 1) | (clkb & 0xe0);
	    SiS_SetReg(SiS_Pr->SiS_P3c4,0x2c,clkb);
	 }
      }
#endif
   } else {
      SiS_SetReg(SiS_Pr->SiS_P3c4,0x2D,0x80);
   }
}