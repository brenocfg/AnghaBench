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
typedef  scalar_t__ uint32_t ;
struct smu_context {int dummy; } ;
typedef  enum amd_dpm_forced_level { ____Placeholder_amd_dpm_forced_level } amd_dpm_forced_level ;

/* Variables and functions */
 int AMD_DPM_FORCED_LEVEL_PROFILE_MIN_MCLK ; 
 int AMD_DPM_FORCED_LEVEL_PROFILE_MIN_SCLK ; 
 int AMD_DPM_FORCED_LEVEL_PROFILE_PEAK ; 
 int /*<<< orphan*/  SMU_MCLK ; 
 int /*<<< orphan*/  SMU_SCLK ; 
 int /*<<< orphan*/  SMU_SOCCLK ; 
 int smu_get_dpm_level_count (struct smu_context*,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static int navi10_get_profiling_clk_mask(struct smu_context *smu,
					 enum amd_dpm_forced_level level,
					 uint32_t *sclk_mask,
					 uint32_t *mclk_mask,
					 uint32_t *soc_mask)
{
	int ret = 0;
	uint32_t level_count = 0;

	if (level == AMD_DPM_FORCED_LEVEL_PROFILE_MIN_SCLK) {
		if (sclk_mask)
			*sclk_mask = 0;
	} else if (level == AMD_DPM_FORCED_LEVEL_PROFILE_MIN_MCLK) {
		if (mclk_mask)
			*mclk_mask = 0;
	} else if (level == AMD_DPM_FORCED_LEVEL_PROFILE_PEAK) {
		if(sclk_mask) {
			ret = smu_get_dpm_level_count(smu, SMU_SCLK, &level_count);
			if (ret)
				return ret;
			*sclk_mask = level_count - 1;
		}

		if(mclk_mask) {
			ret = smu_get_dpm_level_count(smu, SMU_MCLK, &level_count);
			if (ret)
				return ret;
			*mclk_mask = level_count - 1;
		}

		if(soc_mask) {
			ret = smu_get_dpm_level_count(smu, SMU_SOCCLK, &level_count);
			if (ret)
				return ret;
			*soc_mask = level_count - 1;
		}
	}

	return ret;
}