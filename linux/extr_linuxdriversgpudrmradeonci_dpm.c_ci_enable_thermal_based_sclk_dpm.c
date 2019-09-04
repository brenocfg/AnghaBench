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
struct radeon_device {int dummy; } ;
struct ci_power_info {scalar_t__ thermal_sclk_dpm_enabled; } ;
typedef  scalar_t__ PPSMC_Result ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PPSMC_MSG_DISABLE_THERMAL_DPM ; 
 int /*<<< orphan*/  PPSMC_MSG_ENABLE_THERMAL_DPM ; 
 scalar_t__ PPSMC_Result_OK ; 
 struct ci_power_info* ci_get_pi (struct radeon_device*) ; 
 scalar_t__ ci_send_msg_to_smc (struct radeon_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ci_enable_thermal_based_sclk_dpm(struct radeon_device *rdev,
					    bool enable)
{
	struct ci_power_info *pi = ci_get_pi(rdev);
	PPSMC_Result smc_result = PPSMC_Result_OK;

	if (pi->thermal_sclk_dpm_enabled) {
		if (enable)
			smc_result = ci_send_msg_to_smc(rdev, PPSMC_MSG_ENABLE_THERMAL_DPM);
		else
			smc_result = ci_send_msg_to_smc(rdev, PPSMC_MSG_DISABLE_THERMAL_DPM);
	}

	if (smc_result == PPSMC_Result_OK)
		return 0;
	else
		return -EINVAL;
}