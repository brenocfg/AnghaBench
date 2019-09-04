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
struct TYPE_5__ {int forced_level; } ;
struct TYPE_6__ {TYPE_2__ dpm; } ;
struct radeon_device {int usec_timeout; TYPE_3__ pm; } ;
struct TYPE_4__ {int pcie_dpm_enable_mask; int sclk_dpm_enable_mask; int mclk_dpm_enable_mask; } ;
struct ci_power_info {int /*<<< orphan*/  pcie_dpm_key_disabled; TYPE_1__ dpm_level_enable_mask; int /*<<< orphan*/  mclk_dpm_key_disabled; int /*<<< orphan*/  sclk_dpm_key_disabled; } ;
typedef  enum radeon_dpm_forced_level { ____Placeholder_radeon_dpm_forced_level } radeon_dpm_forced_level ;
typedef  scalar_t__ PPSMC_Result ;

/* Variables and functions */
 int CURR_MCLK_INDEX_MASK ; 
 int CURR_MCLK_INDEX_SHIFT ; 
 int CURR_PCIE_INDEX_MASK ; 
 int CURR_PCIE_INDEX_SHIFT ; 
 int CURR_SCLK_INDEX_MASK ; 
 int CURR_SCLK_INDEX_SHIFT ; 
 int EINVAL ; 
 int /*<<< orphan*/  PPSMC_MSG_PCIeDPM_UnForceLevel ; 
 scalar_t__ PPSMC_Result_OK ; 
 int RADEON_DPM_FORCED_LEVEL_AUTO ; 
 int RADEON_DPM_FORCED_LEVEL_HIGH ; 
 int RADEON_DPM_FORCED_LEVEL_LOW ; 
 int RREG32_SMC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TARGET_AND_CURRENT_PROFILE_INDEX ; 
 int /*<<< orphan*/  TARGET_AND_CURRENT_PROFILE_INDEX_1 ; 
 int ci_dpm_force_state_mclk (struct radeon_device*,int) ; 
 int ci_dpm_force_state_pcie (struct radeon_device*,int) ; 
 int ci_dpm_force_state_sclk (struct radeon_device*,int) ; 
 int ci_get_lowest_enabled_level (struct radeon_device*,int) ; 
 struct ci_power_info* ci_get_pi (struct radeon_device*) ; 
 scalar_t__ ci_send_msg_to_smc (struct radeon_device*,int /*<<< orphan*/ ) ; 
 int ci_upload_dpm_level_enable_mask (struct radeon_device*) ; 
 int /*<<< orphan*/  udelay (int) ; 

int ci_dpm_force_performance_level(struct radeon_device *rdev,
				   enum radeon_dpm_forced_level level)
{
	struct ci_power_info *pi = ci_get_pi(rdev);
	u32 tmp, levels, i;
	int ret;

	if (level == RADEON_DPM_FORCED_LEVEL_HIGH) {
		if ((!pi->pcie_dpm_key_disabled) &&
		    pi->dpm_level_enable_mask.pcie_dpm_enable_mask) {
			levels = 0;
			tmp = pi->dpm_level_enable_mask.pcie_dpm_enable_mask;
			while (tmp >>= 1)
				levels++;
			if (levels) {
				ret = ci_dpm_force_state_pcie(rdev, level);
				if (ret)
					return ret;
				for (i = 0; i < rdev->usec_timeout; i++) {
					tmp = (RREG32_SMC(TARGET_AND_CURRENT_PROFILE_INDEX_1) &
					       CURR_PCIE_INDEX_MASK) >> CURR_PCIE_INDEX_SHIFT;
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
				ret = ci_dpm_force_state_sclk(rdev, levels);
				if (ret)
					return ret;
				for (i = 0; i < rdev->usec_timeout; i++) {
					tmp = (RREG32_SMC(TARGET_AND_CURRENT_PROFILE_INDEX) &
					       CURR_SCLK_INDEX_MASK) >> CURR_SCLK_INDEX_SHIFT;
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
				ret = ci_dpm_force_state_mclk(rdev, levels);
				if (ret)
					return ret;
				for (i = 0; i < rdev->usec_timeout; i++) {
					tmp = (RREG32_SMC(TARGET_AND_CURRENT_PROFILE_INDEX) &
					       CURR_MCLK_INDEX_MASK) >> CURR_MCLK_INDEX_SHIFT;
					if (tmp == levels)
						break;
					udelay(1);
				}
			}
		}
	} else if (level == RADEON_DPM_FORCED_LEVEL_LOW) {
		if ((!pi->sclk_dpm_key_disabled) &&
		    pi->dpm_level_enable_mask.sclk_dpm_enable_mask) {
			levels = ci_get_lowest_enabled_level(rdev,
							     pi->dpm_level_enable_mask.sclk_dpm_enable_mask);
			ret = ci_dpm_force_state_sclk(rdev, levels);
			if (ret)
				return ret;
			for (i = 0; i < rdev->usec_timeout; i++) {
				tmp = (RREG32_SMC(TARGET_AND_CURRENT_PROFILE_INDEX) &
				       CURR_SCLK_INDEX_MASK) >> CURR_SCLK_INDEX_SHIFT;
				if (tmp == levels)
					break;
				udelay(1);
			}
		}
		if ((!pi->mclk_dpm_key_disabled) &&
		    pi->dpm_level_enable_mask.mclk_dpm_enable_mask) {
			levels = ci_get_lowest_enabled_level(rdev,
							     pi->dpm_level_enable_mask.mclk_dpm_enable_mask);
			ret = ci_dpm_force_state_mclk(rdev, levels);
			if (ret)
				return ret;
			for (i = 0; i < rdev->usec_timeout; i++) {
				tmp = (RREG32_SMC(TARGET_AND_CURRENT_PROFILE_INDEX) &
				       CURR_MCLK_INDEX_MASK) >> CURR_MCLK_INDEX_SHIFT;
				if (tmp == levels)
					break;
				udelay(1);
			}
		}
		if ((!pi->pcie_dpm_key_disabled) &&
		    pi->dpm_level_enable_mask.pcie_dpm_enable_mask) {
			levels = ci_get_lowest_enabled_level(rdev,
							     pi->dpm_level_enable_mask.pcie_dpm_enable_mask);
			ret = ci_dpm_force_state_pcie(rdev, levels);
			if (ret)
				return ret;
			for (i = 0; i < rdev->usec_timeout; i++) {
				tmp = (RREG32_SMC(TARGET_AND_CURRENT_PROFILE_INDEX_1) &
				       CURR_PCIE_INDEX_MASK) >> CURR_PCIE_INDEX_SHIFT;
				if (tmp == levels)
					break;
				udelay(1);
			}
		}
	} else if (level == RADEON_DPM_FORCED_LEVEL_AUTO) {
		if (!pi->pcie_dpm_key_disabled) {
			PPSMC_Result smc_result;

			smc_result = ci_send_msg_to_smc(rdev,
							PPSMC_MSG_PCIeDPM_UnForceLevel);
			if (smc_result != PPSMC_Result_OK)
				return -EINVAL;
		}
		ret = ci_upload_dpm_level_enable_mask(rdev);
		if (ret)
			return ret;
	}

	rdev->pm.dpm.forced_level = level;

	return 0;
}