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
struct TYPE_2__ {unsigned short Ext_ModeID; } ;

/* Variables and functions */

__attribute__((used)) static int
SiS_SearchModeID(struct SiS_Private *SiS_Pr, unsigned short *ModeNo,
		 unsigned short *ModeIdIndex)
{
	if ((*ModeNo) <= 0x13) {

		if ((*ModeNo) != 0x03)
			return 0;

		(*ModeIdIndex) = 0;

	} else {

		for (*ModeIdIndex = 0;; (*ModeIdIndex)++) {

			if (SiS_Pr->SiS_EModeIDTable[*ModeIdIndex].Ext_ModeID ==
			    (*ModeNo))
				break;

			if (SiS_Pr->SiS_EModeIDTable[*ModeIdIndex].Ext_ModeID ==
			    0xFF)
				return 0;
		}

	}

	return 1;
}