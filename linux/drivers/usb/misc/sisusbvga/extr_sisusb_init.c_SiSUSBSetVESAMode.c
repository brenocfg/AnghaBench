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
struct SiS_Private {TYPE_1__* SiS_EModeIDTable; } ;
struct TYPE_2__ {int Ext_ModeID; unsigned short Ext_VESAID; } ;

/* Variables and functions */
 int SiSUSBSetMode (struct SiS_Private*,unsigned short) ; 
 int /*<<< orphan*/  SiSUSB_InitPtr (struct SiS_Private*) ; 

int SiSUSBSetVESAMode(struct SiS_Private *SiS_Pr, unsigned short VModeNo)
{
	unsigned short ModeNo = 0;
	int i;

	SiSUSB_InitPtr(SiS_Pr);

	if (VModeNo == 0x03) {

		ModeNo = 0x03;

	} else {

		i = 0;
		do {

			if (SiS_Pr->SiS_EModeIDTable[i].Ext_VESAID == VModeNo) {
				ModeNo = SiS_Pr->SiS_EModeIDTable[i].Ext_ModeID;
				break;
			}

		} while (SiS_Pr->SiS_EModeIDTable[i++].Ext_ModeID != 0xff);

	}

	if (!ModeNo)
		return 0;

	return SiSUSBSetMode(SiS_Pr, ModeNo);
}