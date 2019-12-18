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
struct TYPE_3__ {int /*<<< orphan*/  platformCaps; } ;
struct pp_hwmgr {int /*<<< orphan*/  smu_lock; TYPE_2__* current_ps; TYPE_1__ platform_descriptor; int /*<<< orphan*/  pm_en; } ;
struct pp_clock_info {int /*<<< orphan*/  min_eng_clk; int /*<<< orphan*/  max_eng_clk; int /*<<< orphan*/  max_bus_bandwidth; int /*<<< orphan*/  min_bus_bandwidth; int /*<<< orphan*/  max_mem_clk; int /*<<< orphan*/  min_mem_clk; } ;
struct amd_pp_simple_clock_info {scalar_t__ level; int /*<<< orphan*/  member_0; } ;
struct amd_pp_clock_info {scalar_t__ max_clocks_state; int /*<<< orphan*/  min_engine_clock_in_sr; int /*<<< orphan*/  max_engine_clock_in_sr; int /*<<< orphan*/  max_bus_bandwidth; int /*<<< orphan*/  min_bus_bandwidth; int /*<<< orphan*/  max_memory_clock; int /*<<< orphan*/  min_memory_clock; int /*<<< orphan*/  max_engine_clock; int /*<<< orphan*/  min_engine_clock; } ;
struct TYPE_4__ {int /*<<< orphan*/  hardware; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PHM_PerformanceLevelDesignation_Activity ; 
 int /*<<< orphan*/  PHM_PerformanceLevelDesignation_PowerContainment ; 
 int /*<<< orphan*/  PHM_PlatformCaps_PowerContainment ; 
 scalar_t__ PP_DAL_POWERLEVEL_7 ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ phm_cap_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int phm_get_clock_info (struct pp_hwmgr*,int /*<<< orphan*/ *,struct pp_clock_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ phm_get_current_shallow_sleep_clocks (struct pp_hwmgr*,int /*<<< orphan*/ *,struct pp_clock_info*) ; 
 int /*<<< orphan*/  phm_get_dal_power_level (struct pp_hwmgr*,struct amd_pp_simple_clock_info*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static int pp_get_current_clocks(void *handle,
		struct amd_pp_clock_info *clocks)
{
	struct amd_pp_simple_clock_info simple_clocks = { 0 };
	struct pp_clock_info hw_clocks;
	struct pp_hwmgr *hwmgr = handle;
	int ret = 0;

	if (!hwmgr || !hwmgr->pm_en)
		return -EINVAL;

	mutex_lock(&hwmgr->smu_lock);

	phm_get_dal_power_level(hwmgr, &simple_clocks);

	if (phm_cap_enabled(hwmgr->platform_descriptor.platformCaps,
					PHM_PlatformCaps_PowerContainment))
		ret = phm_get_clock_info(hwmgr, &hwmgr->current_ps->hardware,
					&hw_clocks, PHM_PerformanceLevelDesignation_PowerContainment);
	else
		ret = phm_get_clock_info(hwmgr, &hwmgr->current_ps->hardware,
					&hw_clocks, PHM_PerformanceLevelDesignation_Activity);

	if (ret) {
		pr_debug("Error in phm_get_clock_info \n");
		mutex_unlock(&hwmgr->smu_lock);
		return -EINVAL;
	}

	clocks->min_engine_clock = hw_clocks.min_eng_clk;
	clocks->max_engine_clock = hw_clocks.max_eng_clk;
	clocks->min_memory_clock = hw_clocks.min_mem_clk;
	clocks->max_memory_clock = hw_clocks.max_mem_clk;
	clocks->min_bus_bandwidth = hw_clocks.min_bus_bandwidth;
	clocks->max_bus_bandwidth = hw_clocks.max_bus_bandwidth;

	clocks->max_engine_clock_in_sr = hw_clocks.max_eng_clk;
	clocks->min_engine_clock_in_sr = hw_clocks.min_eng_clk;

	if (simple_clocks.level == 0)
		clocks->max_clocks_state = PP_DAL_POWERLEVEL_7;
	else
		clocks->max_clocks_state = simple_clocks.level;

	if (0 == phm_get_current_shallow_sleep_clocks(hwmgr, &hwmgr->current_ps->hardware, &hw_clocks)) {
		clocks->max_engine_clock_in_sr = hw_clocks.max_eng_clk;
		clocks->min_engine_clock_in_sr = hw_clocks.min_eng_clk;
	}
	mutex_unlock(&hwmgr->smu_lock);
	return 0;
}