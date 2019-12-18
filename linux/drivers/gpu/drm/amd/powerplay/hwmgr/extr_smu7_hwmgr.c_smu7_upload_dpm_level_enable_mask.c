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
struct TYPE_2__ {scalar_t__ mclk_dpm_enable_mask; scalar_t__ sclk_dpm_enable_mask; } ;
struct smu7_hwmgr {TYPE_1__ dpm_level_enable_mask; int /*<<< orphan*/  mclk_dpm_key_disabled; int /*<<< orphan*/  sclk_dpm_key_disabled; } ;
struct pp_hwmgr {scalar_t__ pp_table_version; scalar_t__ backend; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPSMC_MSG_MCLKDPM_SetEnabledMask ; 
 int /*<<< orphan*/  PPSMC_MSG_SCLKDPM_SetEnabledMask ; 
 scalar_t__ PP_TABLE_V1 ; 
 int /*<<< orphan*/  phm_apply_dal_min_voltage_request (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smum_send_msg_to_smc_with_parameter (struct pp_hwmgr*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int smu7_upload_dpm_level_enable_mask(struct pp_hwmgr *hwmgr)
{
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);

	if (hwmgr->pp_table_version == PP_TABLE_V1)
		phm_apply_dal_min_voltage_request(hwmgr);
/* TO DO  for v0 iceland and Ci*/

	if (!data->sclk_dpm_key_disabled) {
		if (data->dpm_level_enable_mask.sclk_dpm_enable_mask)
			smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_SCLKDPM_SetEnabledMask,
					data->dpm_level_enable_mask.sclk_dpm_enable_mask);
	}

	if (!data->mclk_dpm_key_disabled) {
		if (data->dpm_level_enable_mask.mclk_dpm_enable_mask)
			smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_MCLKDPM_SetEnabledMask,
					data->dpm_level_enable_mask.mclk_dpm_enable_mask);
	}

	return 0;
}