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
typedef  int uint32_t ;
struct TYPE_4__ {int min_vddc; int max_vddc; } ;
struct smu7_hwmgr {TYPE_2__ odn_dpm_table; } ;
struct pp_hwmgr {scalar_t__ pptable; scalar_t__ backend; } ;
struct phm_ppt_v1_information {struct phm_ppt_v1_clock_voltage_dependency_table* vdd_dep_on_sclk; } ;
struct phm_ppt_v1_clock_voltage_dependency_table {int count; TYPE_1__* entries; } ;
struct TYPE_3__ {int vddc; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomctrl_get_voltage_range (struct pp_hwmgr*,int*,int*) ; 

__attribute__((used)) static void smu7_setup_voltage_range_from_vbios(struct pp_hwmgr *hwmgr)
{
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);
	struct phm_ppt_v1_clock_voltage_dependency_table *dep_sclk_table;
	struct phm_ppt_v1_information *table_info =
			(struct phm_ppt_v1_information *)(hwmgr->pptable);
	uint32_t min_vddc = 0;
	uint32_t max_vddc = 0;

	if (!table_info)
		return;

	dep_sclk_table = table_info->vdd_dep_on_sclk;

	atomctrl_get_voltage_range(hwmgr, &max_vddc, &min_vddc);

	if (min_vddc == 0 || min_vddc > 2000
		|| min_vddc > dep_sclk_table->entries[0].vddc)
		min_vddc = dep_sclk_table->entries[0].vddc;

	if (max_vddc == 0 || max_vddc > 2000
		|| max_vddc < dep_sclk_table->entries[dep_sclk_table->count-1].vddc)
		max_vddc = dep_sclk_table->entries[dep_sclk_table->count-1].vddc;

	data->odn_dpm_table.min_vddc = min_vddc;
	data->odn_dpm_table.max_vddc = max_vddc;
}