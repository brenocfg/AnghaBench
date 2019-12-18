#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pp_hwmgr {TYPE_2__* pptable_func; TYPE_1__* hwmgr_func; int /*<<< orphan*/  pm_en; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* pptable_fini ) (struct pp_hwmgr*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  (* backend_fini ) (struct pp_hwmgr*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  phm_disable_clock_power_gatings (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  phm_disable_dynamic_state_management (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  phm_stop_thermal_controller (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  psm_adjust_power_state_dynamic (struct pp_hwmgr*,int,int /*<<< orphan*/ *) ; 
 int psm_fini_power_state_table (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  psm_set_boot_states (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  stub1 (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  stub2 (struct pp_hwmgr*) ; 

int hwmgr_hw_fini(struct pp_hwmgr *hwmgr)
{
	if (!hwmgr || !hwmgr->pm_en)
		return 0;

	phm_stop_thermal_controller(hwmgr);
	psm_set_boot_states(hwmgr);
	psm_adjust_power_state_dynamic(hwmgr, true, NULL);
	phm_disable_dynamic_state_management(hwmgr);
	phm_disable_clock_power_gatings(hwmgr);

	if (hwmgr->hwmgr_func->backend_fini)
		hwmgr->hwmgr_func->backend_fini(hwmgr);
	if (hwmgr->pptable_func->pptable_fini)
		hwmgr->pptable_func->pptable_fini(hwmgr);
	return psm_fini_power_state_table(hwmgr);
}