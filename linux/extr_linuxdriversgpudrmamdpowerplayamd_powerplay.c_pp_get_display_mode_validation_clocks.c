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
struct TYPE_2__ {int /*<<< orphan*/  platformCaps; } ;
struct pp_hwmgr {int /*<<< orphan*/  smu_lock; TYPE_1__ platform_descriptor; int /*<<< orphan*/  pm_en; } ;
struct amd_pp_simple_clock_info {int /*<<< orphan*/  level; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PHM_PlatformCaps_DynamicPatchPowerState ; 
 int /*<<< orphan*/  PP_DAL_POWERLEVEL_7 ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ phm_cap_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int phm_get_max_high_clocks (struct pp_hwmgr*,struct amd_pp_simple_clock_info*) ; 

__attribute__((used)) static int pp_get_display_mode_validation_clocks(void *handle,
		struct amd_pp_simple_clock_info *clocks)
{
	struct pp_hwmgr *hwmgr = handle;
	int ret = 0;

	if (!hwmgr || !hwmgr->pm_en ||!clocks)
		return -EINVAL;

	clocks->level = PP_DAL_POWERLEVEL_7;

	mutex_lock(&hwmgr->smu_lock);

	if (phm_cap_enabled(hwmgr->platform_descriptor.platformCaps, PHM_PlatformCaps_DynamicPatchPowerState))
		ret = phm_get_max_high_clocks(hwmgr, clocks);

	mutex_unlock(&hwmgr->smu_lock);
	return ret;
}