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
struct SiS_Private {int SiS_VBType; scalar_t__ ChipType; int /*<<< orphan*/  SiS_Part4Port; scalar_t__ SiS_IF_DEF_CONEX; scalar_t__ SiS_IF_DEF_LVDS; } ;

/* Variables and functions */
 int SiS_GetReg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SiS_SetReg (int /*<<< orphan*/ ,int,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetRegAND (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SiS_SetRegOR (int /*<<< orphan*/ ,int,int) ; 
 int VB_NoLCD ; 
 int VB_SIS301 ; 
 int VB_SIS301B ; 
 int VB_SIS301C ; 
 int VB_SIS301LV ; 
 int VB_SIS302B ; 
 int VB_SIS302ELV ; 
 int VB_SIS302LV ; 
 int VB_UMC ; 
 scalar_t__ XGI_20 ; 

__attribute__((used)) static
void
SiS_GetVBType(struct SiS_Private *SiS_Pr)
{
   unsigned short flag = 0, rev = 0, nolcd = 0;
   unsigned short p4_0f, p4_25, p4_27;

   SiS_Pr->SiS_VBType = 0;

   if((SiS_Pr->SiS_IF_DEF_LVDS) || (SiS_Pr->SiS_IF_DEF_CONEX))
      return;

   if(SiS_Pr->ChipType == XGI_20)
      return;

   flag = SiS_GetReg(SiS_Pr->SiS_Part4Port,0x00);

   if(flag > 3)
      return;

   rev = SiS_GetReg(SiS_Pr->SiS_Part4Port,0x01);

   if(flag >= 2) {
      SiS_Pr->SiS_VBType = VB_SIS302B;
   } else if(flag == 1) {
      if(rev >= 0xC0) {
	 SiS_Pr->SiS_VBType = VB_SIS301C;
      } else if(rev >= 0xB0) {
	 SiS_Pr->SiS_VBType = VB_SIS301B;
	 /* Check if 30xB DH version (no LCD support, use Panel Link instead) */
	 nolcd = SiS_GetReg(SiS_Pr->SiS_Part4Port,0x23);
	 if(!(nolcd & 0x02)) SiS_Pr->SiS_VBType |= VB_NoLCD;
      } else {
	 SiS_Pr->SiS_VBType = VB_SIS301;
      }
   }
   if(SiS_Pr->SiS_VBType & (VB_SIS301B | VB_SIS301C | VB_SIS302B)) {
      if(rev >= 0xE0) {
	 flag = SiS_GetReg(SiS_Pr->SiS_Part4Port,0x39);
	 if(flag == 0xff) SiS_Pr->SiS_VBType = VB_SIS302LV;
	 else 	 	  SiS_Pr->SiS_VBType = VB_SIS301C;  /* VB_SIS302ELV; */
      } else if(rev >= 0xD0) {
	 SiS_Pr->SiS_VBType = VB_SIS301LV;
      }
   }
   if(SiS_Pr->SiS_VBType & (VB_SIS301C | VB_SIS301LV | VB_SIS302LV | VB_SIS302ELV)) {
      p4_0f = SiS_GetReg(SiS_Pr->SiS_Part4Port,0x0f);
      p4_25 = SiS_GetReg(SiS_Pr->SiS_Part4Port,0x25);
      p4_27 = SiS_GetReg(SiS_Pr->SiS_Part4Port,0x27);
      SiS_SetRegAND(SiS_Pr->SiS_Part4Port,0x0f,0x7f);
      SiS_SetRegOR(SiS_Pr->SiS_Part4Port,0x25,0x08);
      SiS_SetRegAND(SiS_Pr->SiS_Part4Port,0x27,0xfd);
      if(SiS_GetReg(SiS_Pr->SiS_Part4Port,0x26) & 0x08) {
         SiS_Pr->SiS_VBType |= VB_UMC;
      }
      SiS_SetReg(SiS_Pr->SiS_Part4Port,0x27,p4_27);
      SiS_SetReg(SiS_Pr->SiS_Part4Port,0x25,p4_25);
      SiS_SetReg(SiS_Pr->SiS_Part4Port,0x0f,p4_0f);
   }
}