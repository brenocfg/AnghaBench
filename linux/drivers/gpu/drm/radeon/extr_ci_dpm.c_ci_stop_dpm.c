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
typedef  int /*<<< orphan*/  u32 ;
struct radeon_device {int dummy; } ;
struct ci_power_info {int /*<<< orphan*/  pcie_dpm_key_disabled; } ;
typedef  scalar_t__ PPSMC_Result ;

/* Variables and functions */
 int /*<<< orphan*/  DYNAMIC_PM_EN ; 
 int EINVAL ; 
 int /*<<< orphan*/  GENERAL_PWRMGT ; 
 int /*<<< orphan*/  GLOBAL_PWRMGT_EN ; 
 int /*<<< orphan*/  PPSMC_MSG_PCIeDPM_Disable ; 
 int /*<<< orphan*/  PPSMC_MSG_Voltage_Cntl_Disable ; 
 scalar_t__ PPSMC_Result_OK ; 
 int /*<<< orphan*/  RREG32_SMC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCLK_PWRMGT_CNTL ; 
 int /*<<< orphan*/  WREG32_SMC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ci_enable_sclk_mclk_dpm (struct radeon_device*,int) ; 
 struct ci_power_info* ci_get_pi (struct radeon_device*) ; 
 scalar_t__ ci_send_msg_to_smc (struct radeon_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ci_stop_dpm(struct radeon_device *rdev)
{
	struct ci_power_info *pi = ci_get_pi(rdev);
	PPSMC_Result smc_result;
	int ret;
	u32 tmp;

	tmp = RREG32_SMC(GENERAL_PWRMGT);
	tmp &= ~GLOBAL_PWRMGT_EN;
	WREG32_SMC(GENERAL_PWRMGT, tmp);

	tmp = RREG32_SMC(SCLK_PWRMGT_CNTL);
	tmp &= ~DYNAMIC_PM_EN;
	WREG32_SMC(SCLK_PWRMGT_CNTL, tmp);

	if (!pi->pcie_dpm_key_disabled) {
		smc_result = ci_send_msg_to_smc(rdev, PPSMC_MSG_PCIeDPM_Disable);
		if (smc_result != PPSMC_Result_OK)
			return -EINVAL;
	}

	ret = ci_enable_sclk_mclk_dpm(rdev, false);
	if (ret)
		return ret;

	smc_result = ci_send_msg_to_smc(rdev, PPSMC_MSG_Voltage_Cntl_Disable);
	if (smc_result != PPSMC_Result_OK)
		return -EINVAL;

	return 0;
}