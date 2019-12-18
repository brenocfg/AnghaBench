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
struct pp_hwmgr {int dpm_level; int request_dpm_level; int /*<<< orphan*/  smu_lock; int /*<<< orphan*/  pm_en; } ;
typedef  enum amd_dpm_forced_level { ____Placeholder_amd_dpm_forced_level } amd_dpm_forced_level ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_PP_TASK_READJUST_POWER_STATE ; 
 int EINVAL ; 
 int /*<<< orphan*/  hwmgr_handle_task (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_dpm_en_umd_pstate (struct pp_hwmgr*,int*) ; 

__attribute__((used)) static int pp_dpm_force_performance_level(void *handle,
					enum amd_dpm_forced_level level)
{
	struct pp_hwmgr *hwmgr = handle;

	if (!hwmgr || !hwmgr->pm_en)
		return -EINVAL;

	if (level == hwmgr->dpm_level)
		return 0;

	mutex_lock(&hwmgr->smu_lock);
	pp_dpm_en_umd_pstate(hwmgr, &level);
	hwmgr->request_dpm_level = level;
	hwmgr_handle_task(hwmgr, AMD_PP_TASK_READJUST_POWER_STATE, NULL);
	mutex_unlock(&hwmgr->smu_lock);

	return 0;
}