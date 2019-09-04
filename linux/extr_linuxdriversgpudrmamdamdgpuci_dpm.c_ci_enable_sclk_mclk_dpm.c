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
struct ci_power_info {int /*<<< orphan*/  mclk_dpm_key_disabled; int /*<<< orphan*/  sclk_dpm_key_disabled; } ;
struct amdgpu_device {int dummy; } ;
typedef  scalar_t__ PPSMC_Result ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MC_SEQ_CNTL_3__CAC_EN_MASK ; 
 int /*<<< orphan*/  PPSMC_MSG_DPM_Disable ; 
 int /*<<< orphan*/  PPSMC_MSG_DPM_Enable ; 
 int /*<<< orphan*/  PPSMC_MSG_MCLKDPM_Disable ; 
 int /*<<< orphan*/  PPSMC_MSG_MCLKDPM_Enable ; 
 scalar_t__ PPSMC_Result_OK ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SMC (int /*<<< orphan*/ ,int) ; 
 scalar_t__ amdgpu_ci_send_msg_to_smc (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 struct ci_power_info* ci_get_pi (struct amdgpu_device*) ; 
 int /*<<< orphan*/  ixLCAC_CPL_CNTL ; 
 int /*<<< orphan*/  ixLCAC_MC0_CNTL ; 
 int /*<<< orphan*/  ixLCAC_MC1_CNTL ; 
 int /*<<< orphan*/  mmMC_SEQ_CNTL_3 ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int ci_enable_sclk_mclk_dpm(struct amdgpu_device *adev, bool enable)
{
	struct ci_power_info *pi = ci_get_pi(adev);
	PPSMC_Result smc_result;

	if (enable) {
		if (!pi->sclk_dpm_key_disabled) {
			smc_result = amdgpu_ci_send_msg_to_smc(adev, PPSMC_MSG_DPM_Enable);
			if (smc_result != PPSMC_Result_OK)
				return -EINVAL;
		}

		if (!pi->mclk_dpm_key_disabled) {
			smc_result = amdgpu_ci_send_msg_to_smc(adev, PPSMC_MSG_MCLKDPM_Enable);
			if (smc_result != PPSMC_Result_OK)
				return -EINVAL;

			WREG32_P(mmMC_SEQ_CNTL_3, MC_SEQ_CNTL_3__CAC_EN_MASK,
					~MC_SEQ_CNTL_3__CAC_EN_MASK);

			WREG32_SMC(ixLCAC_MC0_CNTL, 0x05);
			WREG32_SMC(ixLCAC_MC1_CNTL, 0x05);
			WREG32_SMC(ixLCAC_CPL_CNTL, 0x100005);

			udelay(10);

			WREG32_SMC(ixLCAC_MC0_CNTL, 0x400005);
			WREG32_SMC(ixLCAC_MC1_CNTL, 0x400005);
			WREG32_SMC(ixLCAC_CPL_CNTL, 0x500005);
		}
	} else {
		if (!pi->sclk_dpm_key_disabled) {
			smc_result = amdgpu_ci_send_msg_to_smc(adev, PPSMC_MSG_DPM_Disable);
			if (smc_result != PPSMC_Result_OK)
				return -EINVAL;
		}

		if (!pi->mclk_dpm_key_disabled) {
			smc_result = amdgpu_ci_send_msg_to_smc(adev, PPSMC_MSG_MCLKDPM_Disable);
			if (smc_result != PPSMC_Result_OK)
				return -EINVAL;
		}
	}

	return 0;
}