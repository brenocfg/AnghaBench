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
typedef  size_t uint32_t ;
struct TYPE_8__ {size_t count; TYPE_3__* entries; } ;
struct vega10_hwmgr {TYPE_4__ mclk_latency_table; } ;
struct pp_hwmgr {struct vega10_hwmgr* backend; scalar_t__ pptable; } ;
struct pp_clock_levels_with_latency {size_t num_levels; TYPE_2__* data; } ;
struct phm_ppt_v2_information {struct phm_ppt_v1_clock_voltage_dependency_table* vdd_dep_on_mclk; } ;
struct phm_ppt_v1_clock_voltage_dependency_table {size_t count; TYPE_1__* entries; } ;
struct TYPE_7__ {int frequency; int latency; } ;
struct TYPE_6__ {int clocks_in_khz; int latency_in_us; } ;
struct TYPE_5__ {int clk; } ;

/* Variables and functions */

__attribute__((used)) static void vega10_get_memclocks(struct pp_hwmgr *hwmgr,
		struct pp_clock_levels_with_latency *clocks)
{
	struct phm_ppt_v2_information *table_info =
			(struct phm_ppt_v2_information *)hwmgr->pptable;
	struct phm_ppt_v1_clock_voltage_dependency_table *dep_table =
			table_info->vdd_dep_on_mclk;
	struct vega10_hwmgr *data = hwmgr->backend;
	uint32_t j = 0;
	uint32_t i;

	for (i = 0; i < dep_table->count; i++) {
		if (dep_table->entries[i].clk) {

			clocks->data[j].clocks_in_khz =
						dep_table->entries[i].clk * 10;
			data->mclk_latency_table.entries[j].frequency =
							dep_table->entries[i].clk;
			clocks->data[j].latency_in_us =
				data->mclk_latency_table.entries[j].latency = 25;
			j++;
		}
	}
	clocks->num_levels = data->mclk_latency_table.count = j;
}