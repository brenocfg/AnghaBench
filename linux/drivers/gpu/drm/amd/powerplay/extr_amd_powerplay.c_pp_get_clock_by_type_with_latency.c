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
struct pp_clock_levels_with_latency {int dummy; } ;
typedef  enum amd_pp_clock_type { ____Placeholder_amd_pp_clock_type } amd_pp_clock_type ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int phm_get_clock_by_type_with_latency (struct pp_hwmgr*,int,struct pp_clock_levels_with_latency*) ; 

__attribute__((used)) static int pp_get_clock_by_type_with_latency(void *handle,
		enum amd_pp_clock_type type,
		struct pp_clock_levels_with_latency *clocks)
{
	struct pp_hwmgr *hwmgr = handle;
	int ret = 0;

	if (!hwmgr || !hwmgr->pm_en ||!clocks)
		return -EINVAL;

	mutex_lock(&hwmgr->smu_lock);
	ret = phm_get_clock_by_type_with_latency(hwmgr, type, clocks);
	mutex_unlock(&hwmgr->smu_lock);
	return ret;
}