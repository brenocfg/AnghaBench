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
struct ci_power_info {int need_update_smu7_dpm_table; int /*<<< orphan*/  mclk_dpm_key_disabled; int /*<<< orphan*/  sclk_dpm_key_disabled; } ;
struct amdgpu_device {int dummy; } ;
typedef  scalar_t__ PPSMC_Result ;

/* Variables and functions */
 int DPMTABLE_OD_UPDATE_MCLK ; 
 int DPMTABLE_OD_UPDATE_SCLK ; 
 int DPMTABLE_UPDATE_SCLK ; 
 int EINVAL ; 
 int /*<<< orphan*/  PPSMC_MSG_MCLKDPM_FreezeLevel ; 
 int /*<<< orphan*/  PPSMC_MSG_SCLKDPM_FreezeLevel ; 
 scalar_t__ PPSMC_Result_OK ; 
 scalar_t__ amdgpu_ci_send_msg_to_smc (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 struct ci_power_info* ci_get_pi (struct amdgpu_device*) ; 

__attribute__((used)) static int ci_freeze_sclk_mclk_dpm(struct amdgpu_device *adev)
{
	struct ci_power_info *pi = ci_get_pi(adev);
	PPSMC_Result smc_result;

	if (!pi->need_update_smu7_dpm_table)
		return 0;

	if ((!pi->sclk_dpm_key_disabled) &&
	    (pi->need_update_smu7_dpm_table & (DPMTABLE_OD_UPDATE_SCLK | DPMTABLE_UPDATE_SCLK))) {
		smc_result = amdgpu_ci_send_msg_to_smc(adev, PPSMC_MSG_SCLKDPM_FreezeLevel);
		if (smc_result != PPSMC_Result_OK)
			return -EINVAL;
	}

	if ((!pi->mclk_dpm_key_disabled) &&
	    (pi->need_update_smu7_dpm_table & DPMTABLE_OD_UPDATE_MCLK)) {
		smc_result = amdgpu_ci_send_msg_to_smc(adev, PPSMC_MSG_MCLKDPM_FreezeLevel);
		if (smc_result != PPSMC_Result_OK)
			return -EINVAL;
	}

	return 0;
}