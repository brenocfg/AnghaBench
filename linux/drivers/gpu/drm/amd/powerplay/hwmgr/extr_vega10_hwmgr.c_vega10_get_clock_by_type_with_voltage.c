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
struct pp_hwmgr {scalar_t__ pptable; } ;
struct pp_clock_levels_with_voltage {int /*<<< orphan*/  num_levels; TYPE_1__* data; } ;
struct phm_ppt_v2_information {TYPE_3__* vddc_lookup_table; struct phm_ppt_v1_clock_voltage_dependency_table* vdd_dep_on_phyclk; struct phm_ppt_v1_clock_voltage_dependency_table* vdd_dep_on_pixclk; struct phm_ppt_v1_clock_voltage_dependency_table* vdd_dep_on_dispclk; struct phm_ppt_v1_clock_voltage_dependency_table* vdd_dep_on_dcefclk; struct phm_ppt_v1_clock_voltage_dependency_table* vdd_dep_on_mclk; } ;
struct phm_ppt_v1_clock_voltage_dependency_table {size_t count; TYPE_4__* entries; } ;
typedef  enum amd_pp_clock_type { ____Placeholder_amd_pp_clock_type } amd_pp_clock_type ;
struct TYPE_8__ {int clk; size_t vddInd; } ;
struct TYPE_7__ {TYPE_2__* entries; } ;
struct TYPE_6__ {scalar_t__ us_vdd; } ;
struct TYPE_5__ {int clocks_in_khz; size_t voltage_in_mv; } ;

/* Variables and functions */
#define  amd_pp_dcef_clock 132 
#define  amd_pp_disp_clock 131 
#define  amd_pp_mem_clock 130 
#define  amd_pp_phy_clock 129 
#define  amd_pp_pixel_clock 128 

__attribute__((used)) static int vega10_get_clock_by_type_with_voltage(struct pp_hwmgr *hwmgr,
		enum amd_pp_clock_type type,
		struct pp_clock_levels_with_voltage *clocks)
{
	struct phm_ppt_v2_information *table_info =
			(struct phm_ppt_v2_information *)hwmgr->pptable;
	struct phm_ppt_v1_clock_voltage_dependency_table *dep_table;
	uint32_t i;

	switch (type) {
	case amd_pp_mem_clock:
		dep_table = table_info->vdd_dep_on_mclk;
		break;
	case amd_pp_dcef_clock:
		dep_table = table_info->vdd_dep_on_dcefclk;
		break;
	case amd_pp_disp_clock:
		dep_table = table_info->vdd_dep_on_dispclk;
		break;
	case amd_pp_pixel_clock:
		dep_table = table_info->vdd_dep_on_pixclk;
		break;
	case amd_pp_phy_clock:
		dep_table = table_info->vdd_dep_on_phyclk;
		break;
	default:
		return -1;
	}

	for (i = 0; i < dep_table->count; i++) {
		clocks->data[i].clocks_in_khz = dep_table->entries[i].clk  * 10;
		clocks->data[i].voltage_in_mv = (uint32_t)(table_info->vddc_lookup_table->
				entries[dep_table->entries[i].vddInd].us_vdd);
		clocks->num_levels++;
	}

	if (i < dep_table->count)
		return -1;

	return 0;
}