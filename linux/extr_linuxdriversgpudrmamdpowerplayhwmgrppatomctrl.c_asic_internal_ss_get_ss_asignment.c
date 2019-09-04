#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;
struct pp_hwmgr {int /*<<< orphan*/  adev; } ;
struct TYPE_11__ {int speed_spectrum_percentage; int speed_spectrum_rate; void* speed_spectrum_mode; } ;
typedef  TYPE_2__ pp_atomctrl_internal_ss_info ;
struct TYPE_10__ {int /*<<< orphan*/  usStructureSize; } ;
struct TYPE_13__ {TYPE_1__ sHeader; TYPE_3__* asSpreadSpectrum; } ;
struct TYPE_12__ {scalar_t__ const ucClockIndication; int ucSpreadSpectrumMode; int /*<<< orphan*/  usSpreadRateInKhz; int /*<<< orphan*/  usSpreadSpectrumPercentage; int /*<<< orphan*/  ulTargetClockRange; } ;
typedef  TYPE_3__ ATOM_ASIC_SS_ASSIGNMENT ;
typedef  TYPE_4__ ATOM_ASIC_INTERNAL_SS_INFO ;

/* Variables and functions */
 int GET_DATA_TABLE_MAJOR_REVISION (TYPE_4__*) ; 
 int GET_DATA_TABLE_MINOR_REVISION (TYPE_4__*) ; 
 TYPE_4__* asic_internal_ss_get_ss_table (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int,int) ; 
 void* pp_atomctrl_spread_spectrum_mode_center ; 
 void* pp_atomctrl_spread_spectrum_mode_down ; 

__attribute__((used)) static int asic_internal_ss_get_ss_asignment(struct pp_hwmgr *hwmgr,
		const uint8_t clockSource,
		const uint32_t clockSpeed,
		pp_atomctrl_internal_ss_info *ssEntry)
{
	ATOM_ASIC_INTERNAL_SS_INFO *table;
	ATOM_ASIC_SS_ASSIGNMENT *ssInfo;
	int entry_found = 0;

	memset(ssEntry, 0x00, sizeof(pp_atomctrl_internal_ss_info));

	table = asic_internal_ss_get_ss_table(hwmgr->adev);

	if (NULL == table)
		return -1;

	ssInfo = &table->asSpreadSpectrum[0];

	while (((uint8_t *)ssInfo - (uint8_t *)table) <
		le16_to_cpu(table->sHeader.usStructureSize)) {
		if ((clockSource == ssInfo->ucClockIndication) &&
			((uint32_t)clockSpeed <= le32_to_cpu(ssInfo->ulTargetClockRange))) {
			entry_found = 1;
			break;
		}

		ssInfo = (ATOM_ASIC_SS_ASSIGNMENT *)((uint8_t *)ssInfo +
				sizeof(ATOM_ASIC_SS_ASSIGNMENT));
	}

	if (entry_found) {
		ssEntry->speed_spectrum_percentage =
			le16_to_cpu(ssInfo->usSpreadSpectrumPercentage);
		ssEntry->speed_spectrum_rate = le16_to_cpu(ssInfo->usSpreadRateInKhz);

		if (((GET_DATA_TABLE_MAJOR_REVISION(table) == 2) &&
			(GET_DATA_TABLE_MINOR_REVISION(table) >= 2)) ||
			(GET_DATA_TABLE_MAJOR_REVISION(table) == 3)) {
			ssEntry->speed_spectrum_rate /= 100;
		}

		switch (ssInfo->ucSpreadSpectrumMode) {
		case 0:
			ssEntry->speed_spectrum_mode =
				pp_atomctrl_spread_spectrum_mode_down;
			break;
		case 1:
			ssEntry->speed_spectrum_mode =
				pp_atomctrl_spread_spectrum_mode_center;
			break;
		default:
			ssEntry->speed_spectrum_mode =
				pp_atomctrl_spread_spectrum_mode_down;
			break;
		}
	}

	return entry_found ? 0 : 1;
}