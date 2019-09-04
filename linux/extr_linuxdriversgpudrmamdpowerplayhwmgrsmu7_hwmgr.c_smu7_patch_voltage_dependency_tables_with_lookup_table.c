#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct smu7_hwmgr {scalar_t__ vdd_gfx_control; } ;
struct pp_hwmgr {scalar_t__ pptable; scalar_t__ backend; } ;
struct phm_ppt_v1_mm_clock_voltage_dependency_table {size_t count; TYPE_4__* entries; } ;
struct phm_ppt_v1_information {TYPE_6__* vddc_lookup_table; TYPE_2__* vddgfx_lookup_table; struct phm_ppt_v1_mm_clock_voltage_dependency_table* mm_dep_table; struct phm_ppt_v1_clock_voltage_dependency_table* vdd_dep_on_mclk; struct phm_ppt_v1_clock_voltage_dependency_table* vdd_dep_on_sclk; } ;
struct phm_ppt_v1_clock_voltage_dependency_table {size_t count; TYPE_3__* entries; } ;
struct TYPE_12__ {TYPE_5__* entries; } ;
struct TYPE_11__ {int /*<<< orphan*/  us_vdd; } ;
struct TYPE_10__ {size_t vddcInd; int /*<<< orphan*/  vddc; } ;
struct TYPE_9__ {size_t vddInd; int /*<<< orphan*/  vddc; int /*<<< orphan*/  vddgfx; } ;
struct TYPE_8__ {TYPE_1__* entries; } ;
struct TYPE_7__ {int /*<<< orphan*/  us_vdd; } ;

/* Variables and functions */
 scalar_t__ SMU7_VOLTAGE_CONTROL_BY_SVID2 ; 

__attribute__((used)) static int smu7_patch_voltage_dependency_tables_with_lookup_table(
		struct pp_hwmgr *hwmgr)
{
	uint8_t entry_id;
	uint8_t voltage_id;
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);
	struct phm_ppt_v1_information *table_info =
			(struct phm_ppt_v1_information *)(hwmgr->pptable);

	struct phm_ppt_v1_clock_voltage_dependency_table *sclk_table =
			table_info->vdd_dep_on_sclk;
	struct phm_ppt_v1_clock_voltage_dependency_table *mclk_table =
			table_info->vdd_dep_on_mclk;
	struct phm_ppt_v1_mm_clock_voltage_dependency_table *mm_table =
			table_info->mm_dep_table;

	if (data->vdd_gfx_control == SMU7_VOLTAGE_CONTROL_BY_SVID2) {
		for (entry_id = 0; entry_id < sclk_table->count; ++entry_id) {
			voltage_id = sclk_table->entries[entry_id].vddInd;
			sclk_table->entries[entry_id].vddgfx =
				table_info->vddgfx_lookup_table->entries[voltage_id].us_vdd;
		}
	} else {
		for (entry_id = 0; entry_id < sclk_table->count; ++entry_id) {
			voltage_id = sclk_table->entries[entry_id].vddInd;
			sclk_table->entries[entry_id].vddc =
				table_info->vddc_lookup_table->entries[voltage_id].us_vdd;
		}
	}

	for (entry_id = 0; entry_id < mclk_table->count; ++entry_id) {
		voltage_id = mclk_table->entries[entry_id].vddInd;
		mclk_table->entries[entry_id].vddc =
			table_info->vddc_lookup_table->entries[voltage_id].us_vdd;
	}

	for (entry_id = 0; entry_id < mm_table->count; ++entry_id) {
		voltage_id = mm_table->entries[entry_id].vddcInd;
		mm_table->entries[entry_id].vddc =
			table_info->vddc_lookup_table->entries[voltage_id].us_vdd;
	}

	return 0;

}