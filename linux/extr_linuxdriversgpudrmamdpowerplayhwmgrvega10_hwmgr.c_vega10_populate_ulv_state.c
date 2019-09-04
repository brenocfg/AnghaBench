#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
struct TYPE_6__ {scalar_t__ psi1_enable; scalar_t__ psi0_enable; } ;
struct TYPE_4__ {void* UlvPhaseSheddingPsi1; void* UlvPhaseSheddingPsi0; void* UlvGfxclkBypass; void* UlvMp1clkDid; void* UlvSmnclkDid; void* UlvOffsetVid; } ;
struct TYPE_5__ {TYPE_1__ pp_table; } ;
struct vega10_hwmgr {TYPE_3__ vddc_voltage_table; TYPE_2__ smc_state_table; } ;
struct pp_hwmgr {scalar_t__ pptable; struct vega10_hwmgr* backend; } ;
struct phm_ppt_v2_information {scalar_t__ us_ulv_gfxclk_bypass; scalar_t__ us_ulv_mp1clk_did; scalar_t__ us_ulv_smnclk_did; scalar_t__ us_ulv_voltage_offset; } ;

/* Variables and functions */

__attribute__((used)) static int vega10_populate_ulv_state(struct pp_hwmgr *hwmgr)
{
	struct vega10_hwmgr *data = hwmgr->backend;
	struct phm_ppt_v2_information *table_info =
			(struct phm_ppt_v2_information *)(hwmgr->pptable);

	data->smc_state_table.pp_table.UlvOffsetVid =
			(uint8_t)table_info->us_ulv_voltage_offset;

	data->smc_state_table.pp_table.UlvSmnclkDid =
			(uint8_t)(table_info->us_ulv_smnclk_did);
	data->smc_state_table.pp_table.UlvMp1clkDid =
			(uint8_t)(table_info->us_ulv_mp1clk_did);
	data->smc_state_table.pp_table.UlvGfxclkBypass =
			(uint8_t)(table_info->us_ulv_gfxclk_bypass);
	data->smc_state_table.pp_table.UlvPhaseSheddingPsi0 =
			(uint8_t)(data->vddc_voltage_table.psi0_enable);
	data->smc_state_table.pp_table.UlvPhaseSheddingPsi1 =
			(uint8_t)(data->vddc_voltage_table.psi1_enable);

	return 0;
}