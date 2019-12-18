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
struct pp_hwmgr {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGS_IND_REG__SMC ; 
 int /*<<< orphan*/  CG_MULT_THERMAL_STATUS ; 
 int /*<<< orphan*/  CTF_TEMP ; 
 int PHM_READ_VFPF_INDIRECT_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PP_TEMPERATURE_UNITS_PER_CENTIGRADES ; 
 int SMU7_THERMAL_MAXIMUM_TEMP_READING ; 

int smu7_thermal_get_temperature(struct pp_hwmgr *hwmgr)
{
	int temp;

	temp = PHM_READ_VFPF_INDIRECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
			CG_MULT_THERMAL_STATUS, CTF_TEMP);

	/* Bit 9 means the reading is lower than the lowest usable value. */
	if (temp & 0x200)
		temp = SMU7_THERMAL_MAXIMUM_TEMP_READING;
	else
		temp = temp & 0x1ff;

	temp *= PP_TEMPERATURE_UNITS_PER_CENTIGRADES;

	return temp;
}