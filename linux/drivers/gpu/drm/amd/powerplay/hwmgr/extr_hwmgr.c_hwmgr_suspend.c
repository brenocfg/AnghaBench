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
struct pp_hwmgr {int /*<<< orphan*/  pm_en; } ;

/* Variables and functions */
 int /*<<< orphan*/  phm_disable_smc_firmware_ctf (struct pp_hwmgr*) ; 
 int phm_power_down_asic (struct pp_hwmgr*) ; 
 int psm_adjust_power_state_dynamic (struct pp_hwmgr*,int,int /*<<< orphan*/ *) ; 
 int psm_set_boot_states (struct pp_hwmgr*) ; 

int hwmgr_suspend(struct pp_hwmgr *hwmgr)
{
	int ret = 0;

	if (!hwmgr || !hwmgr->pm_en)
		return 0;

	phm_disable_smc_firmware_ctf(hwmgr);
	ret = psm_set_boot_states(hwmgr);
	if (ret)
		return ret;
	ret = psm_adjust_power_state_dynamic(hwmgr, true, NULL);
	if (ret)
		return ret;
	ret = phm_power_down_asic(hwmgr);

	return ret;
}