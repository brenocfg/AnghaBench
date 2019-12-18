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
struct SiS_Private {int /*<<< orphan*/  SiS_P3c4; int /*<<< orphan*/  SiS_P3d4; TYPE_1__* SiS_RefIndex; } ;
struct TYPE_2__ {unsigned short Ext_InfoFlag; } ;

/* Variables and functions */
 unsigned short InterlaceMode ; 
 unsigned short SiS_GetOffset (struct SiS_Private*,unsigned short,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetReg (struct SiS_Private*,int /*<<< orphan*/ ,int,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetRegANDOR (struct SiS_Private*,int /*<<< orphan*/ ,int,int,unsigned short) ; 

__attribute__((used)) static void
SiS_SetCRT1Offset(struct SiS_Private *SiS_Pr, unsigned short ModeNo,
		  unsigned short ModeIdIndex, unsigned short rrti)
{
	unsigned short du = SiS_GetOffset(SiS_Pr, ModeNo, ModeIdIndex, rrti);
	unsigned short infoflag = SiS_Pr->SiS_RefIndex[rrti].Ext_InfoFlag;
	unsigned short temp;

	temp = (du >> 8) & 0x0f;
	SiS_SetRegANDOR(SiS_Pr, SiS_Pr->SiS_P3c4, 0x0E, 0xF0, temp);

	SiS_SetReg(SiS_Pr, SiS_Pr->SiS_P3d4, 0x13, (du & 0xFF));

	if (infoflag & InterlaceMode)
		du >>= 1;

	du <<= 5;
	temp = (du >> 8) & 0xff;
	if (du & 0xff)
		temp++;
	temp++;
	SiS_SetReg(SiS_Pr, SiS_Pr->SiS_P3c4, 0x10, temp);
}