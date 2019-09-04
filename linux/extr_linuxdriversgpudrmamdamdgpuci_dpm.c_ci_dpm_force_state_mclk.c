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
typedef  int u32 ;
struct ci_power_info {int /*<<< orphan*/  mclk_dpm_key_disabled; } ;
struct amdgpu_device {int dummy; } ;
typedef  scalar_t__ PPSMC_Result ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PPSMC_MSG_MCLKDPM_SetEnabledMask ; 
 scalar_t__ PPSMC_Result_OK ; 
 scalar_t__ amdgpu_ci_send_msg_to_smc_with_parameter (struct amdgpu_device*,int /*<<< orphan*/ ,int) ; 
 struct ci_power_info* ci_get_pi (struct amdgpu_device*) ; 

__attribute__((used)) static int ci_dpm_force_state_mclk(struct amdgpu_device *adev, u32 n)
{
	struct ci_power_info *pi = ci_get_pi(adev);

	if (!pi->mclk_dpm_key_disabled) {
		PPSMC_Result smc_result =
			amdgpu_ci_send_msg_to_smc_with_parameter(adev, PPSMC_MSG_MCLKDPM_SetEnabledMask, 1 << n);
		if (smc_result != PPSMC_Result_OK)
			return -EINVAL;
	}

	return 0;
}