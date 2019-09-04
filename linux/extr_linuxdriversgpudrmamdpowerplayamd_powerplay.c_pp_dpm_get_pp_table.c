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
struct pp_hwmgr {int soft_pp_table_size; int /*<<< orphan*/  smu_lock; scalar_t__ soft_pp_table; int /*<<< orphan*/  pm_en; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pp_dpm_get_pp_table(void *handle, char **table)
{
	struct pp_hwmgr *hwmgr = handle;
	int size = 0;

	if (!hwmgr || !hwmgr->pm_en ||!hwmgr->soft_pp_table)
		return -EINVAL;

	mutex_lock(&hwmgr->smu_lock);
	*table = (char *)hwmgr->soft_pp_table;
	size = hwmgr->soft_pp_table_size;
	mutex_unlock(&hwmgr->smu_lock);
	return size;
}