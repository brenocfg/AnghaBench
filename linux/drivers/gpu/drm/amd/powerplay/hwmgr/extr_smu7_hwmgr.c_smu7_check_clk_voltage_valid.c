#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_13__ {TYPE_4__* dpm_levels; } ;
struct TYPE_11__ {TYPE_2__* dpm_levels; } ;
struct TYPE_14__ {TYPE_5__ mclk_table; TYPE_3__ sclk_table; } ;
struct TYPE_9__ {scalar_t__ min_vddc; scalar_t__ max_vddc; } ;
struct smu7_hwmgr {TYPE_6__ golden_dpm_table; TYPE_1__ odn_dpm_table; } ;
struct TYPE_15__ {scalar_t__ engineClock; scalar_t__ memoryClock; } ;
struct TYPE_16__ {TYPE_7__ overdriveLimit; } ;
struct pp_hwmgr {TYPE_8__ platform_descriptor; scalar_t__ backend; } ;
typedef  enum PP_OD_DPM_TABLE_COMMAND { ____Placeholder_PP_OD_DPM_TABLE_COMMAND } PP_OD_DPM_TABLE_COMMAND ;
struct TYPE_12__ {scalar_t__ value; } ;
struct TYPE_10__ {scalar_t__ value; } ;

/* Variables and functions */
 int PP_OD_EDIT_MCLK_VDDC_TABLE ; 
 int PP_OD_EDIT_SCLK_VDDC_TABLE ; 
 int /*<<< orphan*/  pr_info (char*,int,int) ; 

__attribute__((used)) static bool smu7_check_clk_voltage_valid(struct pp_hwmgr *hwmgr,
					enum PP_OD_DPM_TABLE_COMMAND type,
					uint32_t clk,
					uint32_t voltage)
{
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);

	if (voltage < data->odn_dpm_table.min_vddc || voltage > data->odn_dpm_table.max_vddc) {
		pr_info("OD voltage is out of range [%d - %d] mV\n",
						data->odn_dpm_table.min_vddc,
						data->odn_dpm_table.max_vddc);
		return false;
	}

	if (type == PP_OD_EDIT_SCLK_VDDC_TABLE) {
		if (data->golden_dpm_table.sclk_table.dpm_levels[0].value > clk ||
			hwmgr->platform_descriptor.overdriveLimit.engineClock < clk) {
			pr_info("OD engine clock is out of range [%d - %d] MHz\n",
				data->golden_dpm_table.sclk_table.dpm_levels[0].value/100,
				hwmgr->platform_descriptor.overdriveLimit.engineClock/100);
			return false;
		}
	} else if (type == PP_OD_EDIT_MCLK_VDDC_TABLE) {
		if (data->golden_dpm_table.mclk_table.dpm_levels[0].value > clk ||
			hwmgr->platform_descriptor.overdriveLimit.memoryClock < clk) {
			pr_info("OD memory clock is out of range [%d - %d] MHz\n",
				data->golden_dpm_table.mclk_table.dpm_levels[0].value/100,
				hwmgr->platform_descriptor.overdriveLimit.memoryClock/100);
			return false;
		}
	} else {
		return false;
	}

	return true;
}