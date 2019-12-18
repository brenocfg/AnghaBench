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
struct clk_mgr_internal {int smu_ver; } ;

/* Variables and functions */
 int /*<<< orphan*/  VBIOSSMC_MSG_SetMinDeepSleepDcfclk ; 
 int rn_vbios_smu_send_msg_with_param (struct clk_mgr_internal*,int /*<<< orphan*/ ,int) ; 

int rn_vbios_smu_set_min_deep_sleep_dcfclk(struct clk_mgr_internal *clk_mgr, int requested_min_ds_dcfclk_khz)
{
	int actual_min_ds_dcfclk_mhz = -1;

	if (clk_mgr->smu_ver < 0xFFFFFFFF)
		return actual_min_ds_dcfclk_mhz;

	actual_min_ds_dcfclk_mhz = rn_vbios_smu_send_msg_with_param(
			clk_mgr,
			VBIOSSMC_MSG_SetMinDeepSleepDcfclk,
			requested_min_ds_dcfclk_khz / 1000);

	return actual_min_ds_dcfclk_mhz * 1000;
}