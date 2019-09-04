#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_6__ {scalar_t__ sclk_dpm_enable_mask; scalar_t__ mclk_dpm_enable_mask; scalar_t__ pcie_dpm_enable_mask; } ;
struct ci_power_info {int /*<<< orphan*/  pcie_dpm_key_disabled; TYPE_3__ dpm_level_enable_mask; int /*<<< orphan*/  mclk_dpm_key_disabled; int /*<<< orphan*/  sclk_dpm_key_disabled; } ;
struct TYPE_4__ {scalar_t__ forced_level; } ;
struct TYPE_5__ {TYPE_1__ dpm; } ;
struct amdgpu_device {TYPE_2__ pm; } ;
typedef  enum pp_clock_type { ____Placeholder_pp_clock_type } pp_clock_type ;

/* Variables and functions */
 scalar_t__ AMD_DPM_FORCED_LEVEL_MANUAL ; 
 int EINVAL ; 
 int /*<<< orphan*/  PPSMC_MSG_MCLKDPM_SetEnabledMask ; 
 int /*<<< orphan*/  PPSMC_MSG_PCIeDPM_ForceLevel ; 
 int /*<<< orphan*/  PPSMC_MSG_PCIeDPM_UnForceLevel ; 
 int /*<<< orphan*/  PPSMC_MSG_SCLKDPM_SetEnabledMask ; 
#define  PP_MCLK 130 
#define  PP_PCIE 129 
#define  PP_SCLK 128 
 int /*<<< orphan*/  amdgpu_ci_send_msg_to_smc (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_ci_send_msg_to_smc_with_parameter (struct amdgpu_device*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct ci_power_info* ci_get_pi (struct amdgpu_device*) ; 
 int /*<<< orphan*/  ffs (scalar_t__) ; 
 int /*<<< orphan*/  fls (scalar_t__) ; 

__attribute__((used)) static int ci_dpm_force_clock_level(void *handle,
		enum pp_clock_type type, uint32_t mask)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	struct ci_power_info *pi = ci_get_pi(adev);

	if (adev->pm.dpm.forced_level != AMD_DPM_FORCED_LEVEL_MANUAL)
		return -EINVAL;

	if (mask == 0)
		return -EINVAL;

	switch (type) {
	case PP_SCLK:
		if (!pi->sclk_dpm_key_disabled)
			amdgpu_ci_send_msg_to_smc_with_parameter(adev,
					PPSMC_MSG_SCLKDPM_SetEnabledMask,
					pi->dpm_level_enable_mask.sclk_dpm_enable_mask & mask);
		break;

	case PP_MCLK:
		if (!pi->mclk_dpm_key_disabled)
			amdgpu_ci_send_msg_to_smc_with_parameter(adev,
					PPSMC_MSG_MCLKDPM_SetEnabledMask,
					pi->dpm_level_enable_mask.mclk_dpm_enable_mask & mask);
		break;

	case PP_PCIE:
	{
		uint32_t tmp = mask & pi->dpm_level_enable_mask.pcie_dpm_enable_mask;

		if (!pi->pcie_dpm_key_disabled) {
			if (fls(tmp) != ffs(tmp))
				amdgpu_ci_send_msg_to_smc(adev, PPSMC_MSG_PCIeDPM_UnForceLevel);
			else
				amdgpu_ci_send_msg_to_smc_with_parameter(adev,
					PPSMC_MSG_PCIeDPM_ForceLevel,
					fls(tmp) - 1);
		}
		break;
	}
	default:
		break;
	}

	return 0;
}