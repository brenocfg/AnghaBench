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
typedef  enum amd_pp_task { ____Placeholder_amd_pp_task } amd_pp_task ;
typedef  enum amd_pm_state_type { ____Placeholder_amd_pm_state_type } amd_pm_state_type ;

/* Variables and functions */
 int EINVAL ; 
 int hwmgr_handle_task (struct pp_hwmgr*,int,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pp_dpm_dispatch_tasks(void *handle, enum amd_pp_task task_id,
		enum amd_pm_state_type *user_state)
{
	int ret = 0;
	struct pp_hwmgr *hwmgr = handle;

	if (!hwmgr || !hwmgr->pm_en)
		return -EINVAL;

	mutex_lock(&hwmgr->smu_lock);
	ret = hwmgr_handle_task(hwmgr, task_id, user_state);
	mutex_unlock(&hwmgr->smu_lock);

	return ret;
}