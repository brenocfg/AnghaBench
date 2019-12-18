#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ sclk; scalar_t__ mclk; } ;
struct TYPE_11__ {TYPE_3__ max_clock_voltage_on_ac; TYPE_3__ max_clock_voltage_on_dc; } ;
struct TYPE_8__ {int /*<<< orphan*/  bNoFan; } ;
struct TYPE_9__ {TYPE_1__ fanInfo; } ;
struct pp_hwmgr {int pm_en; TYPE_7__* pptable_func; TYPE_6__* hwmgr_func; scalar_t__ adev; TYPE_4__ dyn_state; TYPE_2__ thermal_controller; } ;
struct TYPE_12__ {int dpm_enabled; int /*<<< orphan*/  no_fan; } ;
struct amdgpu_device {TYPE_5__ pm; } ;
struct TYPE_14__ {int (* pptable_init ) (struct pp_hwmgr*) ;int /*<<< orphan*/  (* pptable_fini ) (struct pp_hwmgr*) ;} ;
struct TYPE_13__ {int (* backend_init ) (struct pp_hwmgr*) ;int /*<<< orphan*/  (* backend_fini ) (struct pp_hwmgr*) ;} ;

/* Variables and functions */
 int phm_enable_dynamic_state_management (struct pp_hwmgr*) ; 
 int phm_setup_asic (struct pp_hwmgr*) ; 
 int phm_start_thermal_controller (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int psm_init_power_state_table (struct pp_hwmgr*) ; 
 int psm_set_performance_states (struct pp_hwmgr*) ; 
 int stub1 (struct pp_hwmgr*) ; 
 int stub2 (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  stub3 (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  stub4 (struct pp_hwmgr*) ; 

int hwmgr_hw_init(struct pp_hwmgr *hwmgr)
{
	int ret = 0;

	if (!hwmgr->pm_en)
		return 0;

	if (!hwmgr->pptable_func ||
	    !hwmgr->pptable_func->pptable_init ||
	    !hwmgr->hwmgr_func->backend_init) {
		hwmgr->pm_en = false;
		pr_info("dpm not supported \n");
		return 0;
	}

	ret = hwmgr->pptable_func->pptable_init(hwmgr);
	if (ret)
		goto err;

	((struct amdgpu_device *)hwmgr->adev)->pm.no_fan =
				hwmgr->thermal_controller.fanInfo.bNoFan;

	ret = hwmgr->hwmgr_func->backend_init(hwmgr);
	if (ret)
		goto err1;
 /* make sure dc limits are valid */
	if ((hwmgr->dyn_state.max_clock_voltage_on_dc.sclk == 0) ||
			(hwmgr->dyn_state.max_clock_voltage_on_dc.mclk == 0))
			hwmgr->dyn_state.max_clock_voltage_on_dc =
					hwmgr->dyn_state.max_clock_voltage_on_ac;

	ret = psm_init_power_state_table(hwmgr);
	if (ret)
		goto err2;

	ret = phm_setup_asic(hwmgr);
	if (ret)
		goto err2;

	ret = phm_enable_dynamic_state_management(hwmgr);
	if (ret)
		goto err2;
	ret = phm_start_thermal_controller(hwmgr);
	ret |= psm_set_performance_states(hwmgr);
	if (ret)
		goto err2;

	((struct amdgpu_device *)hwmgr->adev)->pm.dpm_enabled = true;

	return 0;
err2:
	if (hwmgr->hwmgr_func->backend_fini)
		hwmgr->hwmgr_func->backend_fini(hwmgr);
err1:
	if (hwmgr->pptable_func->pptable_fini)
		hwmgr->pptable_func->pptable_fini(hwmgr);
err:
	return ret;
}