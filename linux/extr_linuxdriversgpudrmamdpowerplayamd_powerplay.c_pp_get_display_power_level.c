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
struct pp_hwmgr {int /*<<< orphan*/  smu_lock; int /*<<< orphan*/  pm_en; } ;
struct amd_pp_simple_clock_info {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int phm_get_dal_power_level (struct pp_hwmgr*,struct amd_pp_simple_clock_info*) ; 

__attribute__((used)) static int pp_get_display_power_level(void *handle,
		struct amd_pp_simple_clock_info *output)
{
	struct pp_hwmgr *hwmgr = handle;
	int ret = 0;

	if (!hwmgr || !hwmgr->pm_en ||!output)
		return -EINVAL;

	mutex_lock(&hwmgr->smu_lock);
	ret = phm_get_dal_power_level(hwmgr, output);
	mutex_unlock(&hwmgr->smu_lock);
	return ret;
}