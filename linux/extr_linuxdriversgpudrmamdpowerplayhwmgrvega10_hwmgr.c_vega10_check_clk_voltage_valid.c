#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct vega10_single_dpm_table {TYPE_2__* dpm_levels; } ;
struct vega10_odn_dpm_table {scalar_t__ min_vddc; scalar_t__ max_vddc; } ;
struct TYPE_5__ {struct vega10_single_dpm_table mem_table; struct vega10_single_dpm_table gfx_table; } ;
struct vega10_hwmgr {TYPE_1__ golden_dpm_table; struct vega10_odn_dpm_table odn_dpm_table; } ;
struct TYPE_7__ {scalar_t__ engineClock; scalar_t__ memoryClock; } ;
struct TYPE_8__ {TYPE_3__ overdriveLimit; } ;
struct pp_hwmgr {TYPE_4__ platform_descriptor; struct vega10_hwmgr* backend; } ;
typedef  enum PP_OD_DPM_TABLE_COMMAND { ____Placeholder_PP_OD_DPM_TABLE_COMMAND } PP_OD_DPM_TABLE_COMMAND ;
struct TYPE_6__ {scalar_t__ value; } ;

/* Variables and functions */
 int PP_OD_EDIT_MCLK_VDDC_TABLE ; 
 int PP_OD_EDIT_SCLK_VDDC_TABLE ; 
 int /*<<< orphan*/  pr_info (char*,int,int) ; 

__attribute__((used)) static bool vega10_check_clk_voltage_valid(struct pp_hwmgr *hwmgr,
					enum PP_OD_DPM_TABLE_COMMAND type,
					uint32_t clk,
					uint32_t voltage)
{
	struct vega10_hwmgr *data = hwmgr->backend;
	struct vega10_odn_dpm_table *odn_table = &(data->odn_dpm_table);
	struct vega10_single_dpm_table *golden_table;

	if (voltage < odn_table->min_vddc || voltage > odn_table->max_vddc) {
		pr_info("OD voltage is out of range [%d - %d] mV\n", odn_table->min_vddc, odn_table->max_vddc);
		return false;
	}

	if (type == PP_OD_EDIT_SCLK_VDDC_TABLE) {
		golden_table = &(data->golden_dpm_table.gfx_table);
		if (golden_table->dpm_levels[0].value > clk ||
			hwmgr->platform_descriptor.overdriveLimit.engineClock < clk) {
			pr_info("OD engine clock is out of range [%d - %d] MHz\n",
				golden_table->dpm_levels[0].value/100,
				hwmgr->platform_descriptor.overdriveLimit.engineClock/100);
			return false;
		}
	} else if (type == PP_OD_EDIT_MCLK_VDDC_TABLE) {
		golden_table = &(data->golden_dpm_table.mem_table);
		if (golden_table->dpm_levels[0].value > clk ||
			hwmgr->platform_descriptor.overdriveLimit.memoryClock < clk) {
			pr_info("OD memory clock is out of range [%d - %d] MHz\n",
				golden_table->dpm_levels[0].value/100,
				hwmgr->platform_descriptor.overdriveLimit.memoryClock/100);
			return false;
		}
	} else {
		return false;
	}

	return true;
}