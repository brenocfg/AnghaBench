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
struct smu10_hwmgr {int deep_sleep_dcefclk; scalar_t__ need_min_deep_sleep_dcefclk; } ;
struct pp_hwmgr {scalar_t__ backend; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPSMC_MSG_SetMinDeepSleepDcefclk ; 
 int /*<<< orphan*/  smum_send_msg_to_smc_with_parameter (struct pp_hwmgr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int smu10_set_deep_sleep_dcefclk(struct pp_hwmgr *hwmgr, uint32_t clock)
{
	struct smu10_hwmgr *smu10_data = (struct smu10_hwmgr *)(hwmgr->backend);

	if (smu10_data->need_min_deep_sleep_dcefclk && smu10_data->deep_sleep_dcefclk != clock/100) {
		smu10_data->deep_sleep_dcefclk = clock/100;
		smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_SetMinDeepSleepDcefclk,
					smu10_data->deep_sleep_dcefclk);
	}
	return 0;
}