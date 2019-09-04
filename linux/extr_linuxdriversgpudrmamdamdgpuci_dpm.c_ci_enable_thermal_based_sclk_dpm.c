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
struct ci_power_info {scalar_t__ thermal_sclk_dpm_enabled; } ;
struct amdgpu_device {int dummy; } ;
typedef  scalar_t__ PPSMC_Result ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PPSMC_MSG_DISABLE_THERMAL_DPM ; 
 int /*<<< orphan*/  PPSMC_MSG_ENABLE_THERMAL_DPM ; 
 scalar_t__ PPSMC_Result_OK ; 
 scalar_t__ amdgpu_ci_send_msg_to_smc (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 struct ci_power_info* ci_get_pi (struct amdgpu_device*) ; 

__attribute__((used)) static int ci_enable_thermal_based_sclk_dpm(struct amdgpu_device *adev,
					    bool enable)
{
	struct ci_power_info *pi = ci_get_pi(adev);
	PPSMC_Result smc_result = PPSMC_Result_OK;

	if (pi->thermal_sclk_dpm_enabled) {
		if (enable)
			smc_result = amdgpu_ci_send_msg_to_smc(adev, PPSMC_MSG_ENABLE_THERMAL_DPM);
		else
			smc_result = amdgpu_ci_send_msg_to_smc(adev, PPSMC_MSG_DISABLE_THERMAL_DPM);
	}

	if (smc_result == PPSMC_Result_OK)
		return 0;
	else
		return -EINVAL;
}