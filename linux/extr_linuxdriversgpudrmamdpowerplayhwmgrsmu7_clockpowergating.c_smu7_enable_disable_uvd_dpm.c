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
struct pp_hwmgr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPSMC_MSG_UVDDPM_Disable ; 
 int /*<<< orphan*/  PPSMC_MSG_UVDDPM_Enable ; 
 int smum_send_msg_to_smc (struct pp_hwmgr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smu7_enable_disable_uvd_dpm(struct pp_hwmgr *hwmgr, bool enable)
{
	return smum_send_msg_to_smc(hwmgr, enable ?
			PPSMC_MSG_UVDDPM_Enable :
			PPSMC_MSG_UVDDPM_Disable);
}