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
struct vega10_hwmgr {int /*<<< orphan*/  vddc_leakage; } ;
struct pp_hwmgr {struct vega10_hwmgr* backend; scalar_t__ pptable; } ;
struct TYPE_2__ {int /*<<< orphan*/  vddc; } ;
struct phm_ppt_v2_information {int /*<<< orphan*/  vddc_lookup_table; TYPE_1__ max_clock_voltage_on_dc; } ;

/* Variables and functions */
 int vega10_patch_clock_voltage_limits_with_vddc_leakage (struct pp_hwmgr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int vega10_patch_lookup_table_with_leakage (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int vega10_patch_voltage_dependency_tables_with_lookup_table (struct pp_hwmgr*) ; 
 int vega10_sort_lookup_table (struct pp_hwmgr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vega10_complete_dependency_tables(struct pp_hwmgr *hwmgr)
{
	int result = 0;
	int tmp_result;
	struct phm_ppt_v2_information *table_info =
			(struct phm_ppt_v2_information *)(hwmgr->pptable);
#ifdef PPLIB_VEGA10_EVV_SUPPORT
	struct vega10_hwmgr *data = hwmgr->backend;

	tmp_result = vega10_patch_lookup_table_with_leakage(hwmgr,
			table_info->vddc_lookup_table, &(data->vddc_leakage));
	if (tmp_result)
		result = tmp_result;

	tmp_result = vega10_patch_clock_voltage_limits_with_vddc_leakage(hwmgr,
			&(data->vddc_leakage), &table_info->max_clock_voltage_on_dc.vddc);
	if (tmp_result)
		result = tmp_result;
#endif

	tmp_result = vega10_patch_voltage_dependency_tables_with_lookup_table(hwmgr);
	if (tmp_result)
		result = tmp_result;

	tmp_result = vega10_sort_lookup_table(hwmgr, table_info->vddc_lookup_table);
	if (tmp_result)
		result = tmp_result;

	return result;
}