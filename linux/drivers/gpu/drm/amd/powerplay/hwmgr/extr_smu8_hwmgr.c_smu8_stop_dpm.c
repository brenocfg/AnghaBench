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
struct smu8_hwmgr {int dpm_flags; } ;
struct pp_hwmgr {struct smu8_hwmgr* backend; } ;

/* Variables and functions */
 int DPMFlags_SCLK_Enabled ; 
 int /*<<< orphan*/  PPSMC_MSG_DisableAllSmuFeatures ; 
 unsigned long SCLK_DPM_MASK ; 
 int smum_send_msg_to_smc_with_parameter (struct pp_hwmgr*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int smu8_stop_dpm(struct pp_hwmgr *hwmgr)
{
	int ret = 0;
	struct smu8_hwmgr *data = hwmgr->backend;
	unsigned long dpm_features = 0;

	if (data->dpm_flags & DPMFlags_SCLK_Enabled) {
		dpm_features |= SCLK_DPM_MASK;
		data->dpm_flags &= ~DPMFlags_SCLK_Enabled;
		ret = smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_DisableAllSmuFeatures,
					dpm_features);
	}
	return ret;
}