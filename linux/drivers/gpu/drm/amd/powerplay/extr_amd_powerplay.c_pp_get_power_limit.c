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
typedef  int uint32_t ;
struct TYPE_2__ {int TDPODLimit; } ;
struct pp_hwmgr {int default_power_limit; int power_limit; int /*<<< orphan*/  smu_lock; TYPE_1__ platform_descriptor; scalar_t__ od_enabled; int /*<<< orphan*/  pm_en; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pp_get_power_limit(void *handle, uint32_t *limit, bool default_limit)
{
	struct pp_hwmgr *hwmgr = handle;

	if (!hwmgr || !hwmgr->pm_en ||!limit)
		return -EINVAL;

	mutex_lock(&hwmgr->smu_lock);

	if (default_limit) {
		*limit = hwmgr->default_power_limit;
		if (hwmgr->od_enabled) {
			*limit *= (100 + hwmgr->platform_descriptor.TDPODLimit);
			*limit /= 100;
		}
	}
	else
		*limit = hwmgr->power_limit;

	mutex_unlock(&hwmgr->smu_lock);

	return 0;
}