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
struct pp_display_clock_request {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int phm_display_clock_voltage_request (struct pp_hwmgr*,struct pp_display_clock_request*) ; 

__attribute__((used)) static int pp_display_clock_voltage_request(void *handle,
		struct pp_display_clock_request *clock)
{
	struct pp_hwmgr *hwmgr = handle;
	int ret = 0;

	if (!hwmgr || !hwmgr->pm_en ||!clock)
		return -EINVAL;

	mutex_lock(&hwmgr->smu_lock);
	ret = phm_display_clock_voltage_request(hwmgr, clock);
	mutex_unlock(&hwmgr->smu_lock);

	return ret;
}