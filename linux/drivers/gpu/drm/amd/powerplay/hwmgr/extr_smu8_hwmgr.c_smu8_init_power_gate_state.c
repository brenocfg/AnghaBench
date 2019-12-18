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
struct smu8_hwmgr {int uvd_power_gated; int vce_power_gated; int samu_power_gated; int acp_power_gated; } ;
struct pp_hwmgr {struct smu8_hwmgr* backend; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPSMC_MSG_ACPPowerOFF ; 
 int /*<<< orphan*/  smum_send_msg_to_smc (struct pp_hwmgr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void smu8_init_power_gate_state(struct pp_hwmgr *hwmgr)
{
	struct smu8_hwmgr *data = hwmgr->backend;

	data->uvd_power_gated = false;
	data->vce_power_gated = false;
	data->samu_power_gated = false;
#ifdef CONFIG_DRM_AMD_ACP
	data->acp_power_gated = false;
#else
	smum_send_msg_to_smc(hwmgr, PPSMC_MSG_ACPPowerOFF);
	data->acp_power_gated = true;
#endif

}