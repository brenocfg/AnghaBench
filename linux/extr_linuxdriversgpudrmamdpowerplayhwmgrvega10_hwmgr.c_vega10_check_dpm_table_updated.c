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
typedef  size_t uint32_t ;
struct vega10_odn_dpm_table {int /*<<< orphan*/  vdd_dep_on_sclk; int /*<<< orphan*/  vdd_dep_on_mclk; } ;
struct vega10_hwmgr {int need_update_dpm_table; struct vega10_odn_dpm_table odn_dpm_table; } ;
struct pp_hwmgr {struct phm_ppt_v2_information* pptable; struct vega10_hwmgr* backend; } ;
struct phm_ppt_v2_information {struct phm_ppt_v1_clock_voltage_dependency_table* vdd_dep_on_sclk; struct phm_ppt_v1_clock_voltage_dependency_table* vdd_dep_on_mclk; } ;
struct phm_ppt_v1_clock_voltage_dependency_table {size_t count; TYPE_1__* entries; } ;
struct TYPE_2__ {scalar_t__ vddc; } ;

/* Variables and functions */
 int DPMTABLE_OD_UPDATE_MCLK ; 
 int DPMTABLE_OD_UPDATE_SCLK ; 
 int DPMTABLE_OD_UPDATE_VDDC ; 

__attribute__((used)) static void vega10_check_dpm_table_updated(struct pp_hwmgr *hwmgr)
{
	struct vega10_hwmgr *data = hwmgr->backend;
	struct vega10_odn_dpm_table *odn_table = &(data->odn_dpm_table);
	struct phm_ppt_v2_information *table_info = hwmgr->pptable;
	struct phm_ppt_v1_clock_voltage_dependency_table *dep_table;
	struct phm_ppt_v1_clock_voltage_dependency_table *odn_dep_table;
	uint32_t i;

	dep_table = table_info->vdd_dep_on_mclk;
	odn_dep_table = (struct phm_ppt_v1_clock_voltage_dependency_table *)&(odn_table->vdd_dep_on_mclk);

	for (i = 0; i < dep_table->count; i++) {
		if (dep_table->entries[i].vddc != odn_dep_table->entries[i].vddc) {
			data->need_update_dpm_table |= DPMTABLE_OD_UPDATE_VDDC | DPMTABLE_OD_UPDATE_MCLK;
			return;
		}
	}

	dep_table = table_info->vdd_dep_on_sclk;
	odn_dep_table = (struct phm_ppt_v1_clock_voltage_dependency_table *)&(odn_table->vdd_dep_on_sclk);
	for (i = 0; i < dep_table->count; i++) {
		if (dep_table->entries[i].vddc != odn_dep_table->entries[i].vddc) {
			data->need_update_dpm_table |= DPMTABLE_OD_UPDATE_VDDC | DPMTABLE_OD_UPDATE_SCLK;
			return;
		}
	}

	if (data->need_update_dpm_table & DPMTABLE_OD_UPDATE_VDDC) {
		data->need_update_dpm_table &= ~DPMTABLE_OD_UPDATE_VDDC;
		data->need_update_dpm_table |= DPMTABLE_OD_UPDATE_SCLK | DPMTABLE_OD_UPDATE_MCLK;
	}
}