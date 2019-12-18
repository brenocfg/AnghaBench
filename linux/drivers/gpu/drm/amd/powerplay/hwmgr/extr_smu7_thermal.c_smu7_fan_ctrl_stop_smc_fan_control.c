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
struct pp_hwmgr {int fan_ctrl_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPSMC_StopFanControl ; 
 int smum_send_msg_to_smc (struct pp_hwmgr*,int /*<<< orphan*/ ) ; 

int smu7_fan_ctrl_stop_smc_fan_control(struct pp_hwmgr *hwmgr)
{
	hwmgr->fan_ctrl_enabled = false;
	return smum_send_msg_to_smc(hwmgr, PPSMC_StopFanControl);
}