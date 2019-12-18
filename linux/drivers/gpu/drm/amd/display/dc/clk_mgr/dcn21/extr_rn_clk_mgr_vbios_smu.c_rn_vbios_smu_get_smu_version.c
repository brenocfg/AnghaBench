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
struct clk_mgr_internal {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VBIOSSMC_MSG_GetSmuVersion ; 
 int rn_vbios_smu_send_msg_with_param (struct clk_mgr_internal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rn_vbios_smu_get_smu_version(struct clk_mgr_internal *clk_mgr)
{
	return rn_vbios_smu_send_msg_with_param(
			clk_mgr,
			VBIOSSMC_MSG_GetSmuVersion,
			0);
}