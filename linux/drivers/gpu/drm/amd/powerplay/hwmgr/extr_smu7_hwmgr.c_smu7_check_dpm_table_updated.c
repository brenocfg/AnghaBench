#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_17__ {TYPE_5__* entries; } ;
struct TYPE_13__ {TYPE_1__* entries; } ;
struct smu7_odn_dpm_table {int /*<<< orphan*/  vdd_dependency_on_sclk; int /*<<< orphan*/  vdd_dependency_on_mclk; TYPE_6__ odn_memory_clock_dpm_levels; TYPE_2__ odn_core_clock_dpm_levels; } ;
struct TYPE_19__ {size_t count; TYPE_7__* dpm_levels; } ;
struct TYPE_15__ {size_t count; TYPE_3__* dpm_levels; } ;
struct TYPE_20__ {TYPE_8__ mclk_table; TYPE_4__ sclk_table; } ;
struct smu7_hwmgr {int need_update_smu7_dpm_table; TYPE_9__ dpm_table; struct smu7_odn_dpm_table odn_dpm_table; } ;
struct pp_hwmgr {scalar_t__ pptable; scalar_t__ backend; } ;
struct phm_ppt_v1_information {struct phm_ppt_v1_clock_voltage_dependency_table* vdd_dep_on_sclk; struct phm_ppt_v1_clock_voltage_dependency_table* vdd_dep_on_mclk; } ;
struct phm_ppt_v1_clock_voltage_dependency_table {size_t count; TYPE_10__* entries; } ;
struct TYPE_18__ {scalar_t__ value; } ;
struct TYPE_16__ {scalar_t__ clock; } ;
struct TYPE_14__ {scalar_t__ value; } ;
struct TYPE_12__ {scalar_t__ clock; } ;
struct TYPE_11__ {scalar_t__ vddc; } ;

/* Variables and functions */
 int DPMTABLE_OD_UPDATE_MCLK ; 
 int DPMTABLE_OD_UPDATE_SCLK ; 
 int DPMTABLE_OD_UPDATE_VDDC ; 

__attribute__((used)) static void smu7_check_dpm_table_updated(struct pp_hwmgr *hwmgr)
{
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);
	struct smu7_odn_dpm_table *odn_table = &(data->odn_dpm_table);
	struct phm_ppt_v1_information *table_info =
			(struct phm_ppt_v1_information *)(hwmgr->pptable);
	uint32_t i;

	struct phm_ppt_v1_clock_voltage_dependency_table *dep_table;
	struct phm_ppt_v1_clock_voltage_dependency_table *odn_dep_table;

	if (table_info == NULL)
		return;

	for (i = 0; i < data->dpm_table.sclk_table.count; i++) {
		if (odn_table->odn_core_clock_dpm_levels.entries[i].clock !=
					data->dpm_table.sclk_table.dpm_levels[i].value) {
			data->need_update_smu7_dpm_table |= DPMTABLE_OD_UPDATE_SCLK;
			break;
		}
	}

	for (i = 0; i < data->dpm_table.mclk_table.count; i++) {
		if (odn_table->odn_memory_clock_dpm_levels.entries[i].clock !=
					data->dpm_table.mclk_table.dpm_levels[i].value) {
			data->need_update_smu7_dpm_table |= DPMTABLE_OD_UPDATE_MCLK;
			break;
		}
	}

	dep_table = table_info->vdd_dep_on_mclk;
	odn_dep_table = (struct phm_ppt_v1_clock_voltage_dependency_table *)&(odn_table->vdd_dependency_on_mclk);

	for (i = 0; i < dep_table->count; i++) {
		if (dep_table->entries[i].vddc != odn_dep_table->entries[i].vddc) {
			data->need_update_smu7_dpm_table |= DPMTABLE_OD_UPDATE_VDDC | DPMTABLE_OD_UPDATE_MCLK;
			return;
		}
	}

	dep_table = table_info->vdd_dep_on_sclk;
	odn_dep_table = (struct phm_ppt_v1_clock_voltage_dependency_table *)&(odn_table->vdd_dependency_on_sclk);
	for (i = 0; i < dep_table->count; i++) {
		if (dep_table->entries[i].vddc != odn_dep_table->entries[i].vddc) {
			data->need_update_smu7_dpm_table |= DPMTABLE_OD_UPDATE_VDDC | DPMTABLE_OD_UPDATE_SCLK;
			return;
		}
	}
	if (data->need_update_smu7_dpm_table & DPMTABLE_OD_UPDATE_VDDC) {
		data->need_update_smu7_dpm_table &= ~DPMTABLE_OD_UPDATE_VDDC;
		data->need_update_smu7_dpm_table |= DPMTABLE_OD_UPDATE_SCLK | DPMTABLE_OD_UPDATE_MCLK;
	}
}