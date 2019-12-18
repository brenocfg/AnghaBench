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

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int phm_set_watermarks_for_clocks_ranges (struct pp_hwmgr*,void*) ; 

__attribute__((used)) static int pp_set_watermarks_for_clocks_ranges(void *handle,
		void *clock_ranges)
{
	struct pp_hwmgr *hwmgr = handle;
	int ret = 0;

	if (!hwmgr || !hwmgr->pm_en || !clock_ranges)
		return -EINVAL;

	mutex_lock(&hwmgr->smu_lock);
	ret = phm_set_watermarks_for_clocks_ranges(hwmgr,
			clock_ranges);
	mutex_unlock(&hwmgr->smu_lock);

	return ret;
}