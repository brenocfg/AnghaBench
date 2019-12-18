#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct pp_hwmgr {int dal_power_level; scalar_t__ pptable; } ;
struct phm_ppt_v1_information {struct phm_ppt_v1_clock_voltage_dependency_table* vdd_dep_on_sclk; struct phm_clock_voltage_dependency_table* vddc_dep_on_dal_pwrl; } ;
struct phm_ppt_v1_clock_voltage_dependency_table {size_t count; TYPE_2__* entries; } ;
struct phm_clock_voltage_dependency_table {scalar_t__ count; TYPE_1__* entries; } ;
typedef  enum PP_DAL_POWERLEVEL { ____Placeholder_PP_DAL_POWERLEVEL } PP_DAL_POWERLEVEL ;
struct TYPE_4__ {size_t vddc; } ;
struct TYPE_3__ {int clk; size_t v; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPSMC_MSG_VddC_Request ; 
 int PP_DAL_POWERLEVEL_PERFORMANCE ; 
 int PP_DAL_POWERLEVEL_ULTRALOW ; 
 size_t VOLTAGE_SCALE ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  smum_send_msg_to_smc_with_parameter (struct pp_hwmgr*,int /*<<< orphan*/ ,size_t) ; 

void phm_apply_dal_min_voltage_request(struct pp_hwmgr *hwmgr)
{
	struct phm_ppt_v1_information *table_info =
			(struct phm_ppt_v1_information *)hwmgr->pptable;
	struct phm_clock_voltage_dependency_table *table =
				table_info->vddc_dep_on_dal_pwrl;
	struct phm_ppt_v1_clock_voltage_dependency_table *vddc_table;
	enum PP_DAL_POWERLEVEL dal_power_level = hwmgr->dal_power_level;
	uint32_t req_vddc = 0, req_volt, i;

	if (!table || table->count <= 0
		|| dal_power_level < PP_DAL_POWERLEVEL_ULTRALOW
		|| dal_power_level > PP_DAL_POWERLEVEL_PERFORMANCE)
		return;

	for (i = 0; i < table->count; i++) {
		if (dal_power_level == table->entries[i].clk) {
			req_vddc = table->entries[i].v;
			break;
		}
	}

	vddc_table = table_info->vdd_dep_on_sclk;
	for (i = 0; i < vddc_table->count; i++) {
		if (req_vddc <= vddc_table->entries[i].vddc) {
			req_volt = (((uint32_t)vddc_table->entries[i].vddc) * VOLTAGE_SCALE);
			smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_VddC_Request, req_volt);
			return;
		}
	}
	pr_err("DAL requested level can not"
			" found a available voltage in VDDC DPM Table \n");
}