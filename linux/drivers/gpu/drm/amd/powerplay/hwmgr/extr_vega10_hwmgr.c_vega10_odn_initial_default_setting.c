#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct vega10_odn_vddc_lookup_table {size_t count; TYPE_1__* entries; } ;
struct vega10_odn_dpm_table {int max_vddc; int min_vddc; int /*<<< orphan*/  vdd_dep_on_socclk; int /*<<< orphan*/  vdd_dep_on_mclk; int /*<<< orphan*/  vdd_dep_on_sclk; struct vega10_odn_vddc_lookup_table vddc_lookup_table; } ;
struct vega10_hwmgr {struct vega10_odn_dpm_table odn_dpm_table; } ;
struct TYPE_8__ {scalar_t__ memoryClock; } ;
struct TYPE_9__ {TYPE_3__ overdriveLimit; } ;
struct pp_hwmgr {TYPE_4__ platform_descriptor; scalar_t__ pptable; struct vega10_hwmgr* backend; } ;
struct pp_atomfwctrl_avfs_parameters {int ulMaxVddc; int ulMinVddc; int /*<<< orphan*/  member_0; } ;
struct phm_ppt_v2_information {struct phm_ppt_v1_clock_voltage_dependency_table* vdd_dep_on_socclk; struct phm_ppt_v1_clock_voltage_dependency_table* vdd_dep_on_mclk; struct phm_ppt_v1_clock_voltage_dependency_table* vdd_dep_on_sclk; struct phm_ppt_v1_voltage_lookup_table* vddc_lookup_table; } ;
struct phm_ppt_v1_voltage_lookup_table {size_t count; TYPE_2__* entries; } ;
struct phm_ppt_v1_clock_voltage_dependency_table {int count; TYPE_5__* entries; } ;
struct TYPE_10__ {int vddc; scalar_t__ clk; } ;
struct TYPE_7__ {int /*<<< orphan*/  us_vdd; } ;
struct TYPE_6__ {int /*<<< orphan*/  us_vdd; } ;

/* Variables and functions */
 int pp_atomfwctrl_get_avfs_information (struct pp_hwmgr*,struct pp_atomfwctrl_avfs_parameters*) ; 
 int /*<<< orphan*/  smu_get_voltage_dependency_table_ppt_v1 (struct phm_ppt_v1_clock_voltage_dependency_table*,struct phm_ppt_v1_clock_voltage_dependency_table*) ; 

__attribute__((used)) static int vega10_odn_initial_default_setting(struct pp_hwmgr *hwmgr)
{
	struct vega10_hwmgr *data = hwmgr->backend;
	struct phm_ppt_v2_information *table_info =
			(struct phm_ppt_v2_information *)(hwmgr->pptable);
	struct vega10_odn_dpm_table *odn_table = &(data->odn_dpm_table);
	struct vega10_odn_vddc_lookup_table *od_lookup_table;
	struct phm_ppt_v1_voltage_lookup_table *vddc_lookup_table;
	struct phm_ppt_v1_clock_voltage_dependency_table *dep_table[3];
	struct phm_ppt_v1_clock_voltage_dependency_table *od_table[3];
	struct pp_atomfwctrl_avfs_parameters avfs_params = {0};
	uint32_t i;
	int result;

	result = pp_atomfwctrl_get_avfs_information(hwmgr, &avfs_params);
	if (!result) {
		data->odn_dpm_table.max_vddc = avfs_params.ulMaxVddc;
		data->odn_dpm_table.min_vddc = avfs_params.ulMinVddc;
	}

	od_lookup_table = &odn_table->vddc_lookup_table;
	vddc_lookup_table = table_info->vddc_lookup_table;

	for (i = 0; i < vddc_lookup_table->count; i++)
		od_lookup_table->entries[i].us_vdd = vddc_lookup_table->entries[i].us_vdd;

	od_lookup_table->count = vddc_lookup_table->count;

	dep_table[0] = table_info->vdd_dep_on_sclk;
	dep_table[1] = table_info->vdd_dep_on_mclk;
	dep_table[2] = table_info->vdd_dep_on_socclk;
	od_table[0] = (struct phm_ppt_v1_clock_voltage_dependency_table *)&odn_table->vdd_dep_on_sclk;
	od_table[1] = (struct phm_ppt_v1_clock_voltage_dependency_table *)&odn_table->vdd_dep_on_mclk;
	od_table[2] = (struct phm_ppt_v1_clock_voltage_dependency_table *)&odn_table->vdd_dep_on_socclk;

	for (i = 0; i < 3; i++)
		smu_get_voltage_dependency_table_ppt_v1(dep_table[i], od_table[i]);

	if (odn_table->max_vddc == 0 || odn_table->max_vddc > 2000)
		odn_table->max_vddc = dep_table[0]->entries[dep_table[0]->count - 1].vddc;
	if (odn_table->min_vddc == 0 || odn_table->min_vddc > 2000)
		odn_table->min_vddc = dep_table[0]->entries[0].vddc;

	i = od_table[2]->count - 1;
	od_table[2]->entries[i].clk = hwmgr->platform_descriptor.overdriveLimit.memoryClock > od_table[2]->entries[i].clk ?
					hwmgr->platform_descriptor.overdriveLimit.memoryClock :
					od_table[2]->entries[i].clk;
	od_table[2]->entries[i].vddc = odn_table->max_vddc > od_table[2]->entries[i].vddc ?
					odn_table->max_vddc :
					od_table[2]->entries[i].vddc;

	return 0;
}