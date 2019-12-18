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
struct SiS_Private {int /*<<< orphan*/  SiS_P3da; int /*<<< orphan*/  SiS_P3c0; TYPE_1__* SiS_StandTable; } ;
struct TYPE_2__ {unsigned char* ATTR; } ;

/* Variables and functions */
 int /*<<< orphan*/  SiS_GetRegByte (struct SiS_Private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SiS_SetRegByte (struct SiS_Private*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
SiS_SetATTRegs(struct SiS_Private *SiS_Pr, unsigned short StandTableIndex)
{
	unsigned char ARdata;
	unsigned short i;

	for (i = 0; i <= 0x13; i++) {
		ARdata = SiS_Pr->SiS_StandTable[StandTableIndex].ATTR[i];
		SiS_GetRegByte(SiS_Pr, SiS_Pr->SiS_P3da);
		SiS_SetRegByte(SiS_Pr, SiS_Pr->SiS_P3c0, i);
		SiS_SetRegByte(SiS_Pr, SiS_Pr->SiS_P3c0, ARdata);
	}
	SiS_GetRegByte(SiS_Pr, SiS_Pr->SiS_P3da);
	SiS_SetRegByte(SiS_Pr, SiS_Pr->SiS_P3c0, 0x14);
	SiS_SetRegByte(SiS_Pr, SiS_Pr->SiS_P3c0, 0x00);

	SiS_GetRegByte(SiS_Pr, SiS_Pr->SiS_P3da);
	SiS_SetRegByte(SiS_Pr, SiS_Pr->SiS_P3c0, 0x20);
	SiS_GetRegByte(SiS_Pr, SiS_Pr->SiS_P3da);
}