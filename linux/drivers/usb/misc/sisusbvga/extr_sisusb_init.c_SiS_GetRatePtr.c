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
struct SiS_Private {unsigned short SiS_ModeType; TYPE_2__* SiS_RefIndex; TYPE_1__* SiS_EModeIDTable; int /*<<< orphan*/  SiS_P3d4; } ;
struct TYPE_4__ {unsigned short ModeID; unsigned short Ext_InfoFlag; } ;
struct TYPE_3__ {unsigned short REFindex; } ;

/* Variables and functions */
 unsigned short ModeTypeMask ; 
 int SiS_GetReg (struct SiS_Private*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned short
SiS_GetRatePtr(struct SiS_Private *SiS_Pr, unsigned short ModeNo,
	       unsigned short ModeIdIndex)
{
	unsigned short rrti, i, index, temp;

	if (ModeNo <= 0x13)
		return 0xFFFF;

	index = SiS_GetReg(SiS_Pr, SiS_Pr->SiS_P3d4, 0x33) & 0x0F;
	if (index > 0)
		index--;

	rrti = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].REFindex;
	ModeNo = SiS_Pr->SiS_RefIndex[rrti].ModeID;

	i = 0;
	do {
		if (SiS_Pr->SiS_RefIndex[rrti + i].ModeID != ModeNo)
			break;

		temp =
		    SiS_Pr->SiS_RefIndex[rrti + i].Ext_InfoFlag & ModeTypeMask;
		if (temp < SiS_Pr->SiS_ModeType)
			break;

		i++;
		index--;
	} while (index != 0xFFFF);

	i--;

	return (rrti + i);
}