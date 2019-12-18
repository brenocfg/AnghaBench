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
struct pp_hwmgr {int dpm_level; int /*<<< orphan*/  smu_lock; int /*<<< orphan*/  pm_en; } ;
typedef  enum amd_dpm_forced_level { ____Placeholder_amd_dpm_forced_level } amd_dpm_forced_level ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum amd_dpm_forced_level pp_dpm_get_performance_level(
								void *handle)
{
	struct pp_hwmgr *hwmgr = handle;
	enum amd_dpm_forced_level level;

	if (!hwmgr || !hwmgr->pm_en)
		return -EINVAL;

	mutex_lock(&hwmgr->smu_lock);
	level = hwmgr->dpm_level;
	mutex_unlock(&hwmgr->smu_lock);
	return level;
}