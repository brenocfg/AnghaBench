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
struct pp_hwmgr {scalar_t__ pptable; } ;
struct pp_clock_levels_with_latency {size_t num_levels; TYPE_1__* data; } ;
struct phm_ppt_v2_information {struct phm_ppt_v1_clock_voltage_dependency_table* vdd_dep_on_sclk; } ;
struct phm_ppt_v1_clock_voltage_dependency_table {size_t count; TYPE_2__* entries; } ;
struct TYPE_4__ {int clk; } ;
struct TYPE_3__ {int clocks_in_khz; } ;

/* Variables and functions */

__attribute__((used)) static void vega10_get_sclks(struct pp_hwmgr *hwmgr,
		struct pp_clock_levels_with_latency *clocks)
{
	struct phm_ppt_v2_information *table_info =
			(struct phm_ppt_v2_information *)hwmgr->pptable;
	struct phm_ppt_v1_clock_voltage_dependency_table *dep_table =
			table_info->vdd_dep_on_sclk;
	uint32_t i;

	clocks->num_levels = 0;
	for (i = 0; i < dep_table->count; i++) {
		if (dep_table->entries[i].clk) {
			clocks->data[clocks->num_levels].clocks_in_khz =
					dep_table->entries[i].clk * 10;
			clocks->num_levels++;
		}
	}

}