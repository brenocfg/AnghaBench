#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ gfx_max_level; scalar_t__ mem_max_level; } ;
struct TYPE_11__ {scalar_t__ soft_max_level; } ;
struct TYPE_12__ {TYPE_4__ dpm_state; } ;
struct TYPE_8__ {scalar_t__ soft_max_level; } ;
struct TYPE_9__ {TYPE_1__ dpm_state; } ;
struct TYPE_13__ {TYPE_5__ mem_table; TYPE_2__ gfx_table; } ;
struct TYPE_10__ {int /*<<< orphan*/  mclk_dpm_key_disabled; int /*<<< orphan*/  sclk_dpm_key_disabled; } ;
struct vega10_hwmgr {TYPE_7__ smc_state_table; TYPE_6__ dpm_table; TYPE_3__ registry_data; } ;
struct pp_hwmgr {struct vega10_hwmgr* backend; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPSMC_MSG_SetSoftMaxGfxclkByIndex ; 
 int /*<<< orphan*/  PPSMC_MSG_SetSoftMaxUclkByIndex ; 
 int /*<<< orphan*/  smum_send_msg_to_smc_with_parameter (struct pp_hwmgr*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vega10_apply_dal_minimum_voltage_request (struct pp_hwmgr*) ; 

__attribute__((used)) static int vega10_upload_dpm_max_level(struct pp_hwmgr *hwmgr)
{
	struct vega10_hwmgr *data = hwmgr->backend;

	vega10_apply_dal_minimum_voltage_request(hwmgr);

	if (!data->registry_data.sclk_dpm_key_disabled) {
		if (data->smc_state_table.gfx_max_level !=
			data->dpm_table.gfx_table.dpm_state.soft_max_level) {
			smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_SetSoftMaxGfxclkByIndex,
				data->smc_state_table.gfx_max_level);
			data->dpm_table.gfx_table.dpm_state.soft_max_level =
					data->smc_state_table.gfx_max_level;
		}
	}

	if (!data->registry_data.mclk_dpm_key_disabled) {
		if (data->smc_state_table.mem_max_level !=
			data->dpm_table.mem_table.dpm_state.soft_max_level) {
			smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_SetSoftMaxUclkByIndex,
					data->smc_state_table.mem_max_level);
			data->dpm_table.mem_table.dpm_state.soft_max_level =
					data->smc_state_table.mem_max_level;
		}
	}

	return 0;
}