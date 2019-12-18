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
struct pp_hwmgr {int /*<<< orphan*/  smu_lock; TYPE_1__* hwmgr_func; int /*<<< orphan*/  pm_en; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_asic_baco_capability ) (struct pp_hwmgr*,int*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct pp_hwmgr*,int*) ; 

__attribute__((used)) static int pp_get_asic_baco_capability(void *handle, bool *cap)
{
	struct pp_hwmgr *hwmgr = handle;

	if (!hwmgr)
		return -EINVAL;

	if (!hwmgr->pm_en || !hwmgr->hwmgr_func->get_asic_baco_capability)
		return 0;

	mutex_lock(&hwmgr->smu_lock);
	hwmgr->hwmgr_func->get_asic_baco_capability(hwmgr, cap);
	mutex_unlock(&hwmgr->smu_lock);

	return 0;
}