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
struct smu10_power_state {unsigned int level; TYPE_2__* levels; } ;
struct TYPE_3__ {int /*<<< orphan*/  platformCaps; } ;
struct pp_hwmgr {TYPE_1__ platform_descriptor; } ;
struct pp_hw_power_state {int dummy; } ;
struct TYPE_4__ {int ds_divider_index; int ss_divider_index; scalar_t__ vddc_index; scalar_t__ engine_clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHM_PlatformCaps_SclkDeepSleep ; 
 struct smu10_power_state* cast_smu10_ps (struct pp_hw_power_state*) ; 
 scalar_t__ phm_cap_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smu10_dpm_get_pp_table_entry_callback(
						     struct pp_hwmgr *hwmgr,
					   struct pp_hw_power_state *hw_ps,
							  unsigned int index,
						     const void *clock_info)
{
	struct smu10_power_state *smu10_ps = cast_smu10_ps(hw_ps);

	smu10_ps->levels[index].engine_clock = 0;

	smu10_ps->levels[index].vddc_index = 0;
	smu10_ps->level = index + 1;

	if (phm_cap_enabled(hwmgr->platform_descriptor.platformCaps, PHM_PlatformCaps_SclkDeepSleep)) {
		smu10_ps->levels[index].ds_divider_index = 5;
		smu10_ps->levels[index].ss_divider_index = 5;
	}

	return 0;
}