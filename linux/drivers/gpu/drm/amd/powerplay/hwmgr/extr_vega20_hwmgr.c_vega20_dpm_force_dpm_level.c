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
struct pp_hwmgr {int dummy; } ;
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
 int /*<<< orphan*/  PP_MCLK ; 
 int /*<<< orphan*/  PP_SCLK ; 
 int /*<<< orphan*/  PP_SOCCLK ; 
 int /*<<< orphan*/  vega20_force_clock_level (struct pp_hwmgr*,int /*<<< orphan*/ ,int) ; 
 int vega20_force_dpm_highest (struct pp_hwmgr*) ; 
 int vega20_force_dpm_lowest (struct pp_hwmgr*) ; 
 int vega20_get_profiling_clk_mask (struct pp_hwmgr*,int,int*,int*,int*) ; 
 int vega20_unforce_dpm_levels (struct pp_hwmgr*) ; 

__attribute__((used)) static int vega20_dpm_force_dpm_level(struct pp_hwmgr *hwmgr,
				enum amd_dpm_forced_level level)
{
	int ret = 0;
	uint32_t sclk_mask, mclk_mask, soc_mask;

	switch (level) {
	case AMD_DPM_FORCED_LEVEL_HIGH:
		ret = vega20_force_dpm_highest(hwmgr);
		break;

	case AMD_DPM_FORCED_LEVEL_LOW:
		ret = vega20_force_dpm_lowest(hwmgr);
		break;

	case AMD_DPM_FORCED_LEVEL_AUTO:
		ret = vega20_unforce_dpm_levels(hwmgr);
		break;

	case AMD_DPM_FORCED_LEVEL_PROFILE_STANDARD:
	case AMD_DPM_FORCED_LEVEL_PROFILE_MIN_SCLK:
	case AMD_DPM_FORCED_LEVEL_PROFILE_MIN_MCLK:
	case AMD_DPM_FORCED_LEVEL_PROFILE_PEAK:
		ret = vega20_get_profiling_clk_mask(hwmgr, level, &sclk_mask, &mclk_mask, &soc_mask);
		if (ret)
			return ret;
		vega20_force_clock_level(hwmgr, PP_SCLK, 1 << sclk_mask);
		vega20_force_clock_level(hwmgr, PP_MCLK, 1 << mclk_mask);
		vega20_force_clock_level(hwmgr, PP_SOCCLK, 1 << soc_mask);
		break;

	case AMD_DPM_FORCED_LEVEL_MANUAL:
	case AMD_DPM_FORCED_LEVEL_PROFILE_EXIT:
	default:
		break;
	}

	return ret;
}