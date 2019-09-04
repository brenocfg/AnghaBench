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
typedef  int uint32_t ;
struct TYPE_3__ {struct phm_vce_clock_voltage_dependency_table* vce_clock_voltage_dependency_table; } ;
struct pp_hwmgr {TYPE_1__ dyn_state; } ;
struct phm_vce_clock_voltage_dependency_table {TYPE_2__* entries; scalar_t__ count; } ;
struct TYPE_4__ {int ecclk; } ;

/* Variables and functions */
#define  PPSMC_MSG_SetEclkHardMax 131 
#define  PPSMC_MSG_SetEclkHardMin 130 
#define  PPSMC_MSG_SetEclkSoftMax 129 
#define  PPSMC_MSG_SetEclkSoftMin 128 

__attribute__((used)) static uint32_t smu8_get_eclk_level(struct pp_hwmgr *hwmgr,
					uint32_t clock, uint32_t msg)
{
	int i = 0;
	struct phm_vce_clock_voltage_dependency_table *ptable =
		hwmgr->dyn_state.vce_clock_voltage_dependency_table;

	switch (msg) {
	case PPSMC_MSG_SetEclkSoftMin:
	case PPSMC_MSG_SetEclkHardMin:
		for (i = 0; i < (int)ptable->count; i++) {
			if (clock <= ptable->entries[i].ecclk)
				break;
		}
		break;

	case PPSMC_MSG_SetEclkSoftMax:
	case PPSMC_MSG_SetEclkHardMax:
		for (i = ptable->count - 1; i >= 0; i--) {
			if (clock >= ptable->entries[i].ecclk)
				break;
		}
		break;

	default:
		break;
	}

	return i;
}