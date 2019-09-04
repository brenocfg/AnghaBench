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
struct ci_power_info {int /*<<< orphan*/  pcie_dpm_key_disabled; } ;
struct amdgpu_device {int dummy; } ;
typedef  scalar_t__ PPSMC_Result ;

/* Variables and functions */
 int /*<<< orphan*/  BIF_LNCNT_RESET__RESET_LNCNT_EN_MASK ; 
 int EINVAL ; 
 int /*<<< orphan*/  GENERAL_PWRMGT__GLOBAL_PWRMGT_EN_MASK ; 
 int /*<<< orphan*/  PPSMC_MSG_PCIeDPM_Enable ; 
 int /*<<< orphan*/  PPSMC_MSG_Voltage_Cntl_Enable ; 
 scalar_t__ PPSMC_Result_OK ; 
 int /*<<< orphan*/  RREG32_SMC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCLK_PWRMGT_CNTL__DYNAMIC_PM_EN_MASK ; 
 int /*<<< orphan*/  SMU7_SoftRegisters ; 
 int /*<<< orphan*/  VoltageChangeTimeout ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SMC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ amdgpu_ci_send_msg_to_smc (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 int ci_enable_sclk_mclk_dpm (struct amdgpu_device*,int) ; 
 struct ci_power_info* ci_get_pi (struct amdgpu_device*) ; 
 int /*<<< orphan*/  ci_write_smc_soft_register (struct amdgpu_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ixGENERAL_PWRMGT ; 
 int /*<<< orphan*/  ixSCLK_PWRMGT_CNTL ; 
 int /*<<< orphan*/  mmBIF_LNCNT_RESET ; 
 int /*<<< orphan*/  offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ci_start_dpm(struct amdgpu_device *adev)
{
	struct ci_power_info *pi = ci_get_pi(adev);
	PPSMC_Result smc_result;
	int ret;
	u32 tmp;

	tmp = RREG32_SMC(ixGENERAL_PWRMGT);
	tmp |= GENERAL_PWRMGT__GLOBAL_PWRMGT_EN_MASK;
	WREG32_SMC(ixGENERAL_PWRMGT, tmp);

	tmp = RREG32_SMC(ixSCLK_PWRMGT_CNTL);
	tmp |= SCLK_PWRMGT_CNTL__DYNAMIC_PM_EN_MASK;
	WREG32_SMC(ixSCLK_PWRMGT_CNTL, tmp);

	ci_write_smc_soft_register(adev, offsetof(SMU7_SoftRegisters, VoltageChangeTimeout), 0x1000);

	WREG32_P(mmBIF_LNCNT_RESET, 0, ~BIF_LNCNT_RESET__RESET_LNCNT_EN_MASK);

	smc_result = amdgpu_ci_send_msg_to_smc(adev, PPSMC_MSG_Voltage_Cntl_Enable);
	if (smc_result != PPSMC_Result_OK)
		return -EINVAL;

	ret = ci_enable_sclk_mclk_dpm(adev, true);
	if (ret)
		return ret;

	if (!pi->pcie_dpm_key_disabled) {
		smc_result = amdgpu_ci_send_msg_to_smc(adev, PPSMC_MSG_PCIeDPM_Enable);
		if (smc_result != PPSMC_Result_OK)
			return -EINVAL;
	}

	return 0;
}