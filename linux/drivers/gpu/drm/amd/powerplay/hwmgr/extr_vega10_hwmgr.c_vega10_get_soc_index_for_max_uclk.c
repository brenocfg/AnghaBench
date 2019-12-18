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
struct pp_hwmgr {scalar_t__ pptable; } ;
struct phm_ppt_v2_information {struct phm_ppt_v1_clock_voltage_dependency_table* vdd_dep_on_mclk; } ;
struct phm_ppt_v1_clock_voltage_dependency_table {TYPE_1__* entries; } ;
struct TYPE_2__ {int vddInd; } ;

/* Variables and functions */
 int NUM_UCLK_DPM_LEVELS ; 

__attribute__((used)) static int vega10_get_soc_index_for_max_uclk(struct pp_hwmgr *hwmgr)
{
	struct phm_ppt_v1_clock_voltage_dependency_table *vdd_dep_table_on_mclk;
	struct phm_ppt_v2_information *table_info =
			(struct phm_ppt_v2_information *)(hwmgr->pptable);

	vdd_dep_table_on_mclk  = table_info->vdd_dep_on_mclk;

	return vdd_dep_table_on_mclk->entries[NUM_UCLK_DPM_LEVELS - 1].vddInd + 1;
}