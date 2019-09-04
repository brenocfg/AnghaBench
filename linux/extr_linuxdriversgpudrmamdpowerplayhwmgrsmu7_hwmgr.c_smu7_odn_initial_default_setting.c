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
typedef  size_t uint32_t ;
struct TYPE_12__ {size_t num_of_pl; struct phm_odn_performance_level* entries; } ;
struct TYPE_9__ {size_t num_of_pl; struct phm_odn_performance_level* entries; } ;
struct smu7_odn_dpm_table {int /*<<< orphan*/  vdd_dependency_on_mclk; TYPE_4__ odn_memory_clock_dpm_levels; int /*<<< orphan*/  vdd_dependency_on_sclk; TYPE_1__ odn_core_clock_dpm_levels; } ;
struct TYPE_14__ {size_t count; TYPE_5__* dpm_levels; } ;
struct TYPE_11__ {size_t count; TYPE_2__* dpm_levels; } ;
struct TYPE_15__ {TYPE_6__ mclk_table; TYPE_3__ sclk_table; } ;
struct smu7_hwmgr {TYPE_7__ golden_dpm_table; struct smu7_odn_dpm_table odn_dpm_table; } ;
struct pp_hwmgr {scalar_t__ pptable; scalar_t__ backend; } ;
struct phm_ppt_v1_information {struct phm_ppt_v1_clock_voltage_dependency_table* vdd_dep_on_mclk; struct phm_ppt_v1_clock_voltage_dependency_table* vdd_dep_on_sclk; } ;
struct phm_ppt_v1_clock_voltage_dependency_table {TYPE_8__* entries; } ;
struct phm_odn_performance_level {int enabled; int /*<<< orphan*/  vddc; int /*<<< orphan*/  clock; } ;
struct TYPE_16__ {int /*<<< orphan*/  vddc; } ;
struct TYPE_13__ {int /*<<< orphan*/  value; } ;
struct TYPE_10__ {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  smu_get_voltage_dependency_table_ppt_v1 (struct phm_ppt_v1_clock_voltage_dependency_table*,struct phm_ppt_v1_clock_voltage_dependency_table*) ; 

__attribute__((used)) static int smu7_odn_initial_default_setting(struct pp_hwmgr *hwmgr)
{
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);
	struct smu7_odn_dpm_table *odn_table = &(data->odn_dpm_table);
	struct phm_ppt_v1_information *table_info =
			(struct phm_ppt_v1_information *)(hwmgr->pptable);
	uint32_t i;

	struct phm_ppt_v1_clock_voltage_dependency_table *dep_sclk_table;
	struct phm_ppt_v1_clock_voltage_dependency_table *dep_mclk_table;
	struct phm_odn_performance_level *entries;

	if (table_info == NULL)
		return -EINVAL;

	dep_sclk_table = table_info->vdd_dep_on_sclk;
	dep_mclk_table = table_info->vdd_dep_on_mclk;

	odn_table->odn_core_clock_dpm_levels.num_of_pl =
						data->golden_dpm_table.sclk_table.count;
	entries = odn_table->odn_core_clock_dpm_levels.entries;
	for (i=0; i<data->golden_dpm_table.sclk_table.count; i++) {
		entries[i].clock = data->golden_dpm_table.sclk_table.dpm_levels[i].value;
		entries[i].enabled = true;
		entries[i].vddc = dep_sclk_table->entries[i].vddc;
	}

	smu_get_voltage_dependency_table_ppt_v1(dep_sclk_table,
		(struct phm_ppt_v1_clock_voltage_dependency_table *)&(odn_table->vdd_dependency_on_sclk));

	odn_table->odn_memory_clock_dpm_levels.num_of_pl =
						data->golden_dpm_table.mclk_table.count;
	entries = odn_table->odn_memory_clock_dpm_levels.entries;
	for (i=0; i<data->golden_dpm_table.mclk_table.count; i++) {
		entries[i].clock = data->golden_dpm_table.mclk_table.dpm_levels[i].value;
		entries[i].enabled = true;
		entries[i].vddc = dep_mclk_table->entries[i].vddc;
	}

	smu_get_voltage_dependency_table_ppt_v1(dep_mclk_table,
		(struct phm_ppt_v1_clock_voltage_dependency_table *)&(odn_table->vdd_dependency_on_mclk));

	return 0;
}