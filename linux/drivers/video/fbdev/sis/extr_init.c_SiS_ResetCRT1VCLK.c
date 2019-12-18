#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct SiS_Private {scalar_t__ ChipType; scalar_t__ SiS_IF_DEF_LVDS; int SiS_VBType; int /*<<< orphan*/  SiS_P3c4; TYPE_1__* SiS_VCLKData; } ;
struct TYPE_2__ {int SR2B; int SR2C; } ;

/* Variables and functions */
 scalar_t__ SIS_315H ; 
 scalar_t__ SIS_661 ; 
 int /*<<< orphan*/  SiS_SetReg (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SiS_SetRegANDOR (int /*<<< orphan*/ ,int,int,int) ; 
 int VB_SIS30xBLV ; 

__attribute__((used)) static void
SiS_ResetCRT1VCLK(struct SiS_Private *SiS_Pr)
{
   if(SiS_Pr->ChipType >= SIS_315H) {
      if(SiS_Pr->ChipType < SIS_661) {
	 if(SiS_Pr->SiS_IF_DEF_LVDS == 0) return;
      }
   } else {
      if((SiS_Pr->SiS_IF_DEF_LVDS == 0) &&
	 (!(SiS_Pr->SiS_VBType & VB_SIS30xBLV)) ) {
	 return;
      }
   }

   SiS_SetRegANDOR(SiS_Pr->SiS_P3c4,0x31,0xcf,0x20);
   SiS_SetReg(SiS_Pr->SiS_P3c4,0x2B,SiS_Pr->SiS_VCLKData[1].SR2B);
   SiS_SetReg(SiS_Pr->SiS_P3c4,0x2C,SiS_Pr->SiS_VCLKData[1].SR2C);
   SiS_SetReg(SiS_Pr->SiS_P3c4,0x2D,0x80);
   SiS_SetRegANDOR(SiS_Pr->SiS_P3c4,0x31,0xcf,0x10);
   SiS_SetReg(SiS_Pr->SiS_P3c4,0x2B,SiS_Pr->SiS_VCLKData[0].SR2B);
   SiS_SetReg(SiS_Pr->SiS_P3c4,0x2C,SiS_Pr->SiS_VCLKData[0].SR2C);
   SiS_SetReg(SiS_Pr->SiS_P3c4,0x2D,0x80);
}