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
struct pp_hwmgr {int /*<<< orphan*/  pm_en; TYPE_1__* smumgr_funcs; } ;
struct TYPE_2__ {scalar_t__ (* start_smu ) (struct pp_hwmgr*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int phm_enable_dynamic_state_management (struct pp_hwmgr*) ; 
 int phm_setup_asic (struct pp_hwmgr*) ; 
 int phm_start_thermal_controller (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int psm_adjust_power_state_dynamic (struct pp_hwmgr*,int,int /*<<< orphan*/ *) ; 
 int psm_set_performance_states (struct pp_hwmgr*) ; 
 scalar_t__ stub1 (struct pp_hwmgr*) ; 

int hwmgr_resume(struct pp_hwmgr *hwmgr)
{
	int ret = 0;

	if (!hwmgr)
		return -EINVAL;

	if (hwmgr->smumgr_funcs && hwmgr->smumgr_funcs->start_smu) {
		if (hwmgr->smumgr_funcs->start_smu(hwmgr)) {
			pr_err("smc start failed\n");
			return -EINVAL;
		}
	}

	if (!hwmgr->pm_en)
		return 0;

	ret = phm_setup_asic(hwmgr);
	if (ret)
		return ret;

	ret = phm_enable_dynamic_state_management(hwmgr);
	if (ret)
		return ret;
	ret = phm_start_thermal_controller(hwmgr);
	ret |= psm_set_performance_states(hwmgr);
	if (ret)
		return ret;

	ret = psm_adjust_power_state_dynamic(hwmgr, false, NULL);

	return ret;
}