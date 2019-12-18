#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct smu8_power_state {unsigned int level; TYPE_4__* levels; } ;
struct TYPE_8__ {int hardwareActivityPerformanceLevels; int /*<<< orphan*/  platformCaps; } ;
struct TYPE_6__ {struct phm_clock_voltage_dependency_table* vddc_dependency_on_sclk; } ;
struct pp_hwmgr {TYPE_3__ platform_descriptor; TYPE_1__ dyn_state; } ;
struct pp_hw_power_state {int dummy; } ;
struct phm_clock_voltage_dependency_table {TYPE_2__* entries; } ;
struct TYPE_10__ {size_t index; } ;
struct TYPE_9__ {size_t vddcIndex; int dsDividerIndex; int ssDividerIndex; int /*<<< orphan*/  engineClock; } ;
struct TYPE_7__ {scalar_t__ v; int /*<<< orphan*/  clk; } ;
typedef  TYPE_5__ ATOM_PPLIB_CZ_CLOCK_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  PHM_PlatformCaps_SclkDeepSleep ; 
 struct smu8_power_state* cast_smu8_power_state (struct pp_hw_power_state*) ; 
 scalar_t__ phm_cap_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smu8_dpm_get_pp_table_entry_callback(
						     struct pp_hwmgr *hwmgr,
					   struct pp_hw_power_state *hw_ps,
							  unsigned int index,
						     const void *clock_info)
{
	struct smu8_power_state *smu8_ps = cast_smu8_power_state(hw_ps);

	const ATOM_PPLIB_CZ_CLOCK_INFO *smu8_clock_info = clock_info;

	struct phm_clock_voltage_dependency_table *table =
				    hwmgr->dyn_state.vddc_dependency_on_sclk;
	uint8_t clock_info_index = smu8_clock_info->index;

	if (clock_info_index > (uint8_t)(hwmgr->platform_descriptor.hardwareActivityPerformanceLevels - 1))
		clock_info_index = (uint8_t)(hwmgr->platform_descriptor.hardwareActivityPerformanceLevels - 1);

	smu8_ps->levels[index].engineClock = table->entries[clock_info_index].clk;
	smu8_ps->levels[index].vddcIndex = (uint8_t)table->entries[clock_info_index].v;

	smu8_ps->level = index + 1;

	if (phm_cap_enabled(hwmgr->platform_descriptor.platformCaps, PHM_PlatformCaps_SclkDeepSleep)) {
		smu8_ps->levels[index].dsDividerIndex = 5;
		smu8_ps->levels[index].ssDividerIndex = 5;
	}

	return 0;
}