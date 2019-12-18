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
typedef  int uint32_t ;
struct smu_context {int dummy; } ;
typedef  enum amd_dpm_forced_level { ____Placeholder_amd_dpm_forced_level } amd_dpm_forced_level ;

/* Variables and functions */
#define  AMD_DPM_FORCED_LEVEL_AUTO 136 
#define  AMD_DPM_FORCED_LEVEL_HIGH 135 
#define  AMD_DPM_FORCED_LEVEL_LOW 134 
#define  AMD_DPM_FORCED_LEVEL_MANUAL 133 
#define  AMD_DPM_FORCED_LEVEL_PROFILE_EXIT 132 
#define  AMD_DPM_FORCED_LEVEL_PROFILE_MIN_MCLK 131 
#define  AMD_DPM_FORCED_LEVEL_PROFILE_MIN_SCLK 130 
#define  AMD_DPM_FORCED_LEVEL_PROFILE_PEAK 129 
#define  AMD_DPM_FORCED_LEVEL_PROFILE_STANDARD 128 
 int /*<<< orphan*/  SMU_MCLK ; 
 int /*<<< orphan*/  SMU_SCLK ; 
 int /*<<< orphan*/  SMU_SOCCLK ; 
 int /*<<< orphan*/  smu_force_clk_levels (struct smu_context*,int /*<<< orphan*/ ,int) ; 
 int smu_force_dpm_limit_value (struct smu_context*,int) ; 
 int smu_get_profiling_clk_mask (struct smu_context*,int,int*,int*,int*) ; 
 int smu_unforce_dpm_levels (struct smu_context*) ; 

__attribute__((used)) static int smu_default_set_performance_level(struct smu_context *smu, enum amd_dpm_forced_level level)
{
	int ret = 0;
	uint32_t sclk_mask, mclk_mask, soc_mask;

	switch (level) {
	case AMD_DPM_FORCED_LEVEL_HIGH:
		ret = smu_force_dpm_limit_value(smu, true);
		break;
	case AMD_DPM_FORCED_LEVEL_LOW:
		ret = smu_force_dpm_limit_value(smu, false);
		break;
	case AMD_DPM_FORCED_LEVEL_AUTO:
	case AMD_DPM_FORCED_LEVEL_PROFILE_STANDARD:
		ret = smu_unforce_dpm_levels(smu);
		break;
	case AMD_DPM_FORCED_LEVEL_PROFILE_MIN_SCLK:
	case AMD_DPM_FORCED_LEVEL_PROFILE_MIN_MCLK:
	case AMD_DPM_FORCED_LEVEL_PROFILE_PEAK:
		ret = smu_get_profiling_clk_mask(smu, level,
						 &sclk_mask,
						 &mclk_mask,
						 &soc_mask);
		if (ret)
			return ret;
		smu_force_clk_levels(smu, SMU_SCLK, 1 << sclk_mask);
		smu_force_clk_levels(smu, SMU_MCLK, 1 << mclk_mask);
		smu_force_clk_levels(smu, SMU_SOCCLK, 1 << soc_mask);
		break;
	case AMD_DPM_FORCED_LEVEL_MANUAL:
	case AMD_DPM_FORCED_LEVEL_PROFILE_EXIT:
	default:
		break;
	}
	return ret;
}