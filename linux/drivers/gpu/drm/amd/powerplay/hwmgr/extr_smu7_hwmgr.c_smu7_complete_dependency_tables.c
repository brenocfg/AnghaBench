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
struct smu7_hwmgr {scalar_t__ vdd_gfx_control; int /*<<< orphan*/  vddc_leakage; int /*<<< orphan*/  vddcgfx_leakage; } ;
struct pp_hwmgr {scalar_t__ pptable; scalar_t__ backend; } ;
struct TYPE_2__ {int /*<<< orphan*/  vddc; int /*<<< orphan*/  vddgfx; } ;
struct phm_ppt_v1_information {int /*<<< orphan*/  vddc_lookup_table; int /*<<< orphan*/  vddgfx_lookup_table; TYPE_1__ max_clock_voltage_on_dc; } ;

/* Variables and functions */
 scalar_t__ SMU7_VOLTAGE_CONTROL_BY_SVID2 ; 
 int smu7_calc_mm_voltage_dependency_table (struct pp_hwmgr*) ; 
 int smu7_calc_voltage_dependency_tables (struct pp_hwmgr*) ; 
 int smu7_patch_clock_voltage_limits_with_vddc_leakage (struct pp_hwmgr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int smu7_patch_lookup_table_with_leakage (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smu7_patch_ppt_v1_with_vdd_leakage (struct pp_hwmgr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int smu7_patch_voltage_dependency_tables_with_lookup_table (struct pp_hwmgr*) ; 
 int smu7_sort_lookup_table (struct pp_hwmgr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smu7_complete_dependency_tables(struct pp_hwmgr *hwmgr)
{
	int result = 0;
	int tmp_result;
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);
	struct phm_ppt_v1_information *table_info =
			(struct phm_ppt_v1_information *)(hwmgr->pptable);

	if (data->vdd_gfx_control == SMU7_VOLTAGE_CONTROL_BY_SVID2) {
		tmp_result = smu7_patch_lookup_table_with_leakage(hwmgr,
			table_info->vddgfx_lookup_table, &(data->vddcgfx_leakage));
		if (tmp_result != 0)
			result = tmp_result;

		smu7_patch_ppt_v1_with_vdd_leakage(hwmgr,
			&table_info->max_clock_voltage_on_dc.vddgfx, &(data->vddcgfx_leakage));
	} else {

		tmp_result = smu7_patch_lookup_table_with_leakage(hwmgr,
				table_info->vddc_lookup_table, &(data->vddc_leakage));
		if (tmp_result)
			result = tmp_result;

		tmp_result = smu7_patch_clock_voltage_limits_with_vddc_leakage(hwmgr,
				&(data->vddc_leakage), &table_info->max_clock_voltage_on_dc.vddc);
		if (tmp_result)
			result = tmp_result;
	}

	tmp_result = smu7_patch_voltage_dependency_tables_with_lookup_table(hwmgr);
	if (tmp_result)
		result = tmp_result;

	tmp_result = smu7_calc_voltage_dependency_tables(hwmgr);
	if (tmp_result)
		result = tmp_result;

	tmp_result = smu7_calc_mm_voltage_dependency_table(hwmgr);
	if (tmp_result)
		result = tmp_result;

	tmp_result = smu7_sort_lookup_table(hwmgr, table_info->vddgfx_lookup_table);
	if (tmp_result)
		result = tmp_result;

	tmp_result = smu7_sort_lookup_table(hwmgr, table_info->vddc_lookup_table);
	if (tmp_result)
		result = tmp_result;

	return result;
}