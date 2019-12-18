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
struct smu8_hwmgr {int /*<<< orphan*/  dpm_flags; } ;
struct pp_hwmgr {struct smu8_hwmgr* backend; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPMFlags_SCLK_Enabled ; 
 int /*<<< orphan*/  PPSMC_MSG_EnableAllSmuFeatures ; 
 int /*<<< orphan*/  SCLK_DPM_MASK ; 
 int smum_send_msg_to_smc_with_parameter (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smu8_start_dpm(struct pp_hwmgr *hwmgr)
{
	struct smu8_hwmgr *data = hwmgr->backend;

	data->dpm_flags |= DPMFlags_SCLK_Enabled;

	return smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_EnableAllSmuFeatures,
				SCLK_DPM_MASK);
}