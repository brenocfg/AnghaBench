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
struct TYPE_5__ {struct phm_clock_voltage_dependency_table* vddc_dependency_on_mclk; } ;
struct pp_hwmgr {scalar_t__ pp_table_version; TYPE_2__ dyn_state; scalar_t__ pptable; } ;
struct phm_ppt_v1_information {struct phm_ppt_v1_clock_voltage_dependency_table* vdd_dep_on_mclk; } ;
struct phm_ppt_v1_clock_voltage_dependency_table {int count; TYPE_1__* entries; } ;
struct phm_clock_voltage_dependency_table {int count; TYPE_3__* entries; } ;
struct amd_pp_clocks {int* clock; int count; int /*<<< orphan*/ * latency; } ;
struct TYPE_6__ {int clk; } ;
struct TYPE_4__ {int clk; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PP_TABLE_V0 ; 
 scalar_t__ PP_TABLE_V1 ; 
 int /*<<< orphan*/  smu7_get_mem_latency (struct pp_hwmgr*,int) ; 

__attribute__((used)) static int smu7_get_mclks(struct pp_hwmgr *hwmgr, struct amd_pp_clocks *clocks)
{
	struct phm_ppt_v1_information *table_info =
			(struct phm_ppt_v1_information *)hwmgr->pptable;
	struct phm_ppt_v1_clock_voltage_dependency_table *dep_mclk_table;
	int i;
	struct phm_clock_voltage_dependency_table *mclk_table;

	if (hwmgr->pp_table_version == PP_TABLE_V1) {
		if (table_info == NULL)
			return -EINVAL;
		dep_mclk_table = table_info->vdd_dep_on_mclk;
		for (i = 0; i < dep_mclk_table->count; i++) {
			clocks->clock[i] = dep_mclk_table->entries[i].clk * 10;
			clocks->latency[i] = smu7_get_mem_latency(hwmgr,
						dep_mclk_table->entries[i].clk);
		}
		clocks->count = dep_mclk_table->count;
	} else if (hwmgr->pp_table_version == PP_TABLE_V0) {
		mclk_table = hwmgr->dyn_state.vddc_dependency_on_mclk;
		for (i = 0; i < mclk_table->count; i++)
			clocks->clock[i] = mclk_table->entries[i].clk * 10;
		clocks->count = mclk_table->count;
	}
	return 0;
}