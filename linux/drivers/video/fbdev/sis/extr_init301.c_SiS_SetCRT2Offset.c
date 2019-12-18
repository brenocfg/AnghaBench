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
struct SiS_Private {int SiS_VBInfo; int /*<<< orphan*/  SiS_Part1Port; } ;

/* Variables and functions */
 int SetInSlaveMode ; 
 unsigned short SiS_GetOffset (struct SiS_Private*,unsigned short,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetReg (int /*<<< orphan*/ ,int,unsigned char) ; 

__attribute__((used)) static void
SiS_SetCRT2Offset(struct SiS_Private *SiS_Pr, unsigned short ModeNo, unsigned short ModeIdIndex,
		unsigned short RRTI)
{
   unsigned short offset;
   unsigned char  temp;

   if(SiS_Pr->SiS_VBInfo & SetInSlaveMode) return;

   offset = SiS_GetOffset(SiS_Pr,ModeNo,ModeIdIndex,RRTI);

   SiS_SetReg(SiS_Pr->SiS_Part1Port,0x07,(offset & 0xFF));
   SiS_SetReg(SiS_Pr->SiS_Part1Port,0x09,(offset >> 8));

   temp = (unsigned char)(((offset >> 3) & 0xFF) + 1);
   if(offset & 0x07) temp++;
   SiS_SetReg(SiS_Pr->SiS_Part1Port,0x03,temp);
}