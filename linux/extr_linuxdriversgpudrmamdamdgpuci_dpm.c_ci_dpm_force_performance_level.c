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
typedef  int u32 ;
struct TYPE_4__ {int pcie_dpm_enable_mask; int sclk_dpm_enable_mask; int mclk_dpm_enable_mask; } ;
struct ci_power_info {int /*<<< orphan*/  pcie_dpm_key_disabled; TYPE_1__ dpm_level_enable_mask; int /*<<< orphan*/  mclk_dpm_key_disabled; int /*<<< orphan*/  sclk_dpm_key_disabled; } ;
struct TYPE_5__ {int forced_level; } ;
struct TYPE_6__ {TYPE_2__ dpm; } ;
struct amdgpu_device {int usec_timeout; TYPE_3__ pm; } ;
typedef  enum amd_dpm_forced_level { ____Placeholder_amd_dpm_forced_level } amd_dpm_forced_level ;
typedef  scalar_t__ PPSMC_Result ;

/* Variables and functions */
 int AMD_DPM_FORCED_LEVEL_AUTO ; 
 int AMD_DPM_FORCED_LEVEL_HIGH ; 
 int AMD_DPM_FORCED_LEVEL_LOW ; 
 int EINVAL ; 
 int /*<<< orphan*/  PPSMC_MSG_PCIeDPM_UnForceLevel ; 
 scalar_t__ PPSMC_Result_OK ; 
 int RREG32_SMC (int /*<<< orphan*/ ) ; 
 int TARGET_AND_CURRENT_PROFILE_INDEX_1__CURR_PCIE_INDEX_MASK ; 
 int TARGET_AND_CURRENT_PROFILE_INDEX_1__CURR_PCIE_INDEX__SHIFT ; 
 int TARGET_AND_CURRENT_PROFILE_INDEX__CURR_MCLK_INDEX_MASK ; 
 int TARGET_AND_CURRENT_PROFILE_INDEX__CURR_MCLK_INDEX__SHIFT ; 
 int TARGET_AND_CURRENT_PROFILE_INDEX__CURR_SCLK_INDEX_MASK ; 
 int TARGET_AND_CURRENT_PROFILE_INDEX__CURR_SCLK_INDEX__SHIFT ; 
 scalar_t__ amdgpu_ci_send_msg_to_smc (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 int ci_dpm_force_state_mclk (struct amdgpu_device*,int) ; 
 int ci_dpm_force_state_pcie (struct amdgpu_device*,int) ; 
 int ci_dpm_force_state_sclk (struct amdgpu_device*,int) ; 
 int ci_get_lowest_enabled_level (struct amdgpu_device*,int) ; 
 struct ci_power_info* ci_get_pi (struct amdgpu_device*) ; 
 int ci_upload_dpm_level_enable_mask (struct amdgpu_device*) ; 
 int /*<<< orphan*/  ixTARGET_AND_CURRENT_PROFILE_INDEX ; 
 int /*<<< orphan*/  ixTARGET_AND_CURRENT_PROFILE_INDEX_1 ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int ci_dpm_force_performance_level(void *handle,
					  enum amd_dpm_forced_level level)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	struct ci_power_info *pi = ci_get_pi(adev);
	u32 tmp, levels, i;
	int ret;

	if (level == AMD_DPM_FORCED_LEVEL_HIGH) {
		if ((!pi->pcie_dpm_key_disabled) &&
		    pi->dpm_level_enable_mask.pcie_dpm_enable_mask) {
			levels = 0;
			tmp = pi->dpm_level_enable_mask.pcie_dpm_enable_mask;
			while (tmp >>= 1)
				levels++;
			if (levels) {
				ret = ci_dpm_force_state_pcie(adev, level);
				if (ret)
					return ret;
				for (i = 0; i < adev->usec_timeout; i++) {
					tmp = (RREG32_SMC(ixTARGET_AND_CURRENT_PROFILE_INDEX_1) &
					TARGET_AND_CURRENT_PROFILE_INDEX_1__CURR_PCIE_INDEX_MASK) >>
					TARGET_AND_CURRENT_PROFILE_INDEX_1__CURR_PCIE_INDEX__SHIFT;
					if (tmp == levels)
						break;
					udelay(1);
				}
			}
		}
		if ((!pi->sclk_dpm_key_disabled) &&
		    pi->dpm_level_enable_mask.sclk_dpm_enable_mask) {
			levels = 0;
			tmp = pi->dpm_level_enable_mask.sclk_dpm_enable_mask;
			while (tmp >>= 1)
				levels++;
			if (levels) {
				ret = ci_dpm_force_state_sclk(adev, levels);
				if (ret)
					return ret;
				for (i = 0; i < adev->usec_timeout; i++) {
					tmp = (RREG32_SMC(ixTARGET_AND_CURRENT_PROFILE_INDEX) &
					TARGET_AND_CURRENT_PROFILE_INDEX__CURR_SCLK_INDEX_MASK) >>
					TARGET_AND_CURRENT_PROFILE_INDEX__CURR_SCLK_INDEX__SHIFT;
					if (tmp == levels)
						break;
					udelay(1);
				}
			}
		}
		if ((!pi->mclk_dpm_key_disabled) &&
		    pi->dpm_level_enable_mask.mclk_dpm_enable_mask) {
			levels = 0;
			tmp = pi->dpm_level_enable_mask.mclk_dpm_enable_mask;
			while (tmp >>= 1)
				levels++;
			if (levels) {
				ret = ci_dpm_force_state_mclk(adev, levels);
				if (ret)
					return ret;
				for (i = 0; i < adev->usec_timeout; i++) {
					tmp = (RREG32_SMC(ixTARGET_AND_CURRENT_PROFILE_INDEX) &
					TARGET_AND_CURRENT_PROFILE_INDEX__CURR_MCLK_INDEX_MASK) >>
					TARGET_AND_CURRENT_PROFILE_INDEX__CURR_MCLK_INDEX__SHIFT;
					if (tmp == levels)
						break;
					udelay(1);
				}
			}
		}
	} else if (level == AMD_DPM_FORCED_LEVEL_LOW) {
		if ((!pi->sclk_dpm_key_disabled) &&
		    pi->dpm_level_enable_mask.sclk_dpm_enable_mask) {
			levels = ci_get_lowest_enabled_level(adev,
							     pi->dpm_level_enable_mask.sclk_dpm_enable_mask);
			ret = ci_dpm_force_state_sclk(adev, levels);
			if (ret)
				return ret;
			for (i = 0; i < adev->usec_timeout; i++) {
				tmp = (RREG32_SMC(ixTARGET_AND_CURRENT_PROFILE_INDEX) &
				TARGET_AND_CURRENT_PROFILE_INDEX__CURR_SCLK_INDEX_MASK) >>
				TARGET_AND_CURRENT_PROFILE_INDEX__CURR_SCLK_INDEX__SHIFT;
				if (tmp == levels)
					break;
				udelay(1);
			}
		}
		if ((!pi->mclk_dpm_key_disabled) &&
		    pi->dpm_level_enable_mask.mclk_dpm_enable_mask) {
			levels = ci_get_lowest_enabled_level(adev,
							     pi->dpm_level_enable_mask.mclk_dpm_enable_mask);
			ret = ci_dpm_force_state_mclk(adev, levels);
			if (ret)
				return ret;
			for (i = 0; i < adev->usec_timeout; i++) {
				tmp = (RREG32_SMC(ixTARGET_AND_CURRENT_PROFILE_INDEX) &
				TARGET_AND_CURRENT_PROFILE_INDEX__CURR_MCLK_INDEX_MASK) >>
				TARGET_AND_CURRENT_PROFILE_INDEX__CURR_MCLK_INDEX__SHIFT;
				if (tmp == levels)
					break;
				udelay(1);
			}
		}
		if ((!pi->pcie_dpm_key_disabled) &&
		    pi->dpm_level_enable_mask.pcie_dpm_enable_mask) {
			levels = ci_get_lowest_enabled_level(adev,
							     pi->dpm_level_enable_mask.pcie_dpm_enable_mask);
			ret = ci_dpm_force_state_pcie(adev, levels);
			if (ret)
				return ret;
			for (i = 0; i < adev->usec_timeout; i++) {
				tmp = (RREG32_SMC(ixTARGET_AND_CURRENT_PROFILE_INDEX_1) &
				TARGET_AND_CURRENT_PROFILE_INDEX_1__CURR_PCIE_INDEX_MASK) >>
				TARGET_AND_CURRENT_PROFILE_INDEX_1__CURR_PCIE_INDEX__SHIFT;
				if (tmp == levels)
					break;
				udelay(1);
			}
		}
	} else if (level == AMD_DPM_FORCED_LEVEL_AUTO) {
		if (!pi->pcie_dpm_key_disabled) {
			PPSMC_Result smc_result;

			smc_result = amdgpu_ci_send_msg_to_smc(adev,
							       PPSMC_MSG_PCIeDPM_UnForceLevel);
			if (smc_result != PPSMC_Result_OK)
				return -EINVAL;
		}
		ret = ci_upload_dpm_level_enable_mask(adev);
		if (ret)
			return ret;
	}

	adev->pm.dpm.forced_level = level;

	return 0;
}