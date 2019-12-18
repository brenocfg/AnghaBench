#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_2__ {int sclk_dpm_enable_mask; } ;
struct smu7_hwmgr {TYPE_1__ dpm_level_enable_mask; } ;
struct pp_hwmgr {int power_profile_mode; scalar_t__ backend; } ;
typedef  enum PP_SMC_POWER_PROFILE { ____Placeholder_PP_SMC_POWER_PROFILE } PP_SMC_POWER_PROFILE ;

/* Variables and functions */
 int /*<<< orphan*/  PP_SCLK ; 
 int PP_SMC_POWER_PROFILE_COMPUTE ; 
 int /*<<< orphan*/  smu7_force_clock_level (struct pp_hwmgr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void smu7_patch_compute_profile_mode(struct pp_hwmgr *hwmgr,
					enum PP_SMC_POWER_PROFILE requst)
{
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);
	uint32_t tmp, level;

	if (requst == PP_SMC_POWER_PROFILE_COMPUTE) {
		if (data->dpm_level_enable_mask.sclk_dpm_enable_mask) {
			level = 0;
			tmp = data->dpm_level_enable_mask.sclk_dpm_enable_mask;
			while (tmp >>= 1)
				level++;
			if (level > 0)
				smu7_force_clock_level(hwmgr, PP_SCLK, 3 << (level-1));
		}
	} else if (hwmgr->power_profile_mode == PP_SMC_POWER_PROFILE_COMPUTE) {
		smu7_force_clock_level(hwmgr, PP_SCLK, data->dpm_level_enable_mask.sclk_dpm_enable_mask);
	}
}