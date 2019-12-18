#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  platformCaps; } ;
struct pp_hwmgr {TYPE_2__* display_config; TYPE_1__ platform_descriptor; } ;
struct TYPE_4__ {scalar_t__ min_core_set_clock_in_sr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHM_PlatformCaps_SclkDeepSleep ; 
 int /*<<< orphan*/  PPSMC_MSG_SetMinDeepSleepSclk ; 
 int /*<<< orphan*/  PP_DBG_LOG (char*,scalar_t__) ; 
 scalar_t__ SMU8_MIN_DEEP_SLEEP_SCLK ; 
 scalar_t__ phm_cap_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smum_send_msg_to_smc_with_parameter (struct pp_hwmgr*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int smu8_set_deep_sleep_sclk_threshold(struct pp_hwmgr *hwmgr)
{
	if (phm_cap_enabled(hwmgr->platform_descriptor.platformCaps,
				PHM_PlatformCaps_SclkDeepSleep)) {
		uint32_t clks = hwmgr->display_config->min_core_set_clock_in_sr;
		if (clks == 0)
			clks = SMU8_MIN_DEEP_SLEEP_SCLK;

		PP_DBG_LOG("Setting Deep Sleep Clock: %d\n", clks);

		smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_SetMinDeepSleepSclk,
				clks);
	}

	return 0;
}