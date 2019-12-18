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
typedef  size_t uint32_t ;
struct pp_hwmgr {long power_profile_mode; int gfxoff_state_changed_by_workload; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PPSMC_MSG_ActiveProcessNotify ; 
 long PP_SMC_POWER_PROFILE_COMPUTE ; 
 int conv_power_profile_to_pplib_workload (long) ; 
 int /*<<< orphan*/  pr_err (char*,long) ; 
 int /*<<< orphan*/  smu10_gfx_off_control (struct pp_hwmgr*,int) ; 
 scalar_t__ smu10_is_raven1_refresh (struct pp_hwmgr*) ; 
 int smum_send_msg_to_smc_with_parameter (struct pp_hwmgr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int smu10_set_power_profile_mode(struct pp_hwmgr *hwmgr, long *input, uint32_t size)
{
	int workload_type = 0;
	int result = 0;

	if (input[size] > PP_SMC_POWER_PROFILE_COMPUTE) {
		pr_err("Invalid power profile mode %ld\n", input[size]);
		return -EINVAL;
	}
	if (hwmgr->power_profile_mode == input[size])
		return 0;

	/* conv PP_SMC_POWER_PROFILE* to WORKLOAD_PPLIB_*_BIT */
	workload_type =
		conv_power_profile_to_pplib_workload(input[size]);
	if (workload_type &&
	    smu10_is_raven1_refresh(hwmgr) &&
	    !hwmgr->gfxoff_state_changed_by_workload) {
		smu10_gfx_off_control(hwmgr, false);
		hwmgr->gfxoff_state_changed_by_workload = true;
	}
	result = smum_send_msg_to_smc_with_parameter(hwmgr, PPSMC_MSG_ActiveProcessNotify,
						1 << workload_type);
	if (!result)
		hwmgr->power_profile_mode = input[size];
	if (workload_type && hwmgr->gfxoff_state_changed_by_workload) {
		smu10_gfx_off_control(hwmgr, true);
		hwmgr->gfxoff_state_changed_by_workload = false;
	}

	return 0;
}