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
struct TYPE_3__ {struct phm_uvd_clock_voltage_dependency_table* uvd_clock_voltage_dependency_table; } ;
struct pp_hwmgr {TYPE_1__ dyn_state; } ;
struct phm_uvd_clock_voltage_dependency_table {TYPE_2__* entries; scalar_t__ count; } ;
struct TYPE_4__ {int vclk; } ;

/* Variables and functions */
#define  PPSMC_MSG_SetUvdHardMax 131 
#define  PPSMC_MSG_SetUvdHardMin 130 
#define  PPSMC_MSG_SetUvdSoftMax 129 
#define  PPSMC_MSG_SetUvdSoftMin 128 

__attribute__((used)) static uint32_t smu8_get_uvd_level(struct pp_hwmgr *hwmgr,
					uint32_t clock, uint32_t msg)
{
	int i = 0;
	struct phm_uvd_clock_voltage_dependency_table *ptable =
		hwmgr->dyn_state.uvd_clock_voltage_dependency_table;

	switch (msg) {
	case PPSMC_MSG_SetUvdSoftMin:
	case PPSMC_MSG_SetUvdHardMin:
		for (i = 0; i < (int)ptable->count; i++) {
			if (clock <= ptable->entries[i].vclk)
				break;
		}
		break;

	case PPSMC_MSG_SetUvdSoftMax:
	case PPSMC_MSG_SetUvdHardMax:
		for (i = ptable->count - 1; i >= 0; i--) {
			if (clock >= ptable->entries[i].vclk)
				break;
		}
		break;

	default:
		break;
	}

	return i;
}