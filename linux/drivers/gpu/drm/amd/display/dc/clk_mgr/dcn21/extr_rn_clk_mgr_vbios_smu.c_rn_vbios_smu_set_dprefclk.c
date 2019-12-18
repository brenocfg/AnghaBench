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
struct TYPE_2__ {int dprefclk_khz; } ;
struct clk_mgr_internal {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  VBIOSSMC_MSG_SetDprefclkFreq ; 
 int rn_vbios_smu_send_msg_with_param (struct clk_mgr_internal*,int /*<<< orphan*/ ,int) ; 

int rn_vbios_smu_set_dprefclk(struct clk_mgr_internal *clk_mgr)
{
	int actual_dprefclk_set_mhz = -1;

	actual_dprefclk_set_mhz = rn_vbios_smu_send_msg_with_param(
			clk_mgr,
			VBIOSSMC_MSG_SetDprefclkFreq,
			clk_mgr->base.dprefclk_khz / 1000);

	/* TODO: add code for programing DP DTO, currently this is down by command table */

	return actual_dprefclk_set_mhz * 1000;
}