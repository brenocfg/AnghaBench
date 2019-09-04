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

/* Variables and functions */

__attribute__((used)) static int vega12_get_current_activity_percent(
		struct pp_hwmgr *hwmgr,
		uint32_t *activity_percent)
{
	int ret = 0;
	uint32_t current_activity = 50;

#if 0
	ret = smum_send_msg_to_smc_with_parameter(hwmgr, PPSMC_MSG_GetAverageGfxActivity, 0);
	if (!ret) {
		current_activity = smum_get_argument(hwmgr);
		if (current_activity > 100) {
			PP_ASSERT(false,
				  "[GetCurrentActivityPercent] Activity Percentage Exceeds 100!");
			current_activity = 100;
		}
	} else
		PP_ASSERT(false,
			"[GetCurrentActivityPercent] Attempt To Send Get Average Graphics Activity to SMU Failed!");
#endif
	*activity_percent = current_activity;

	return ret;
}