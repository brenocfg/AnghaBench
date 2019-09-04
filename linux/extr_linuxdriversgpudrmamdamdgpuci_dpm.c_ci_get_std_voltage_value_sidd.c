#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  size_t u16 ;
struct atom_voltage_table_entry {size_t value; } ;
struct TYPE_11__ {scalar_t__ count; TYPE_3__* entries; } ;
struct TYPE_9__ {scalar_t__ count; TYPE_1__* entries; } ;
struct TYPE_12__ {TYPE_4__ cac_leakage_table; TYPE_2__ vddc_dependency_on_sclk; } ;
struct TYPE_13__ {TYPE_5__ dyn_state; } ;
struct TYPE_14__ {TYPE_6__ dpm; } ;
struct amdgpu_device {TYPE_7__ pm; } ;
struct TYPE_10__ {size_t vddc; size_t leakage; } ;
struct TYPE_8__ {scalar_t__ v; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t VOLTAGE_SCALE ; 

__attribute__((used)) static int ci_get_std_voltage_value_sidd(struct amdgpu_device *adev,
					 struct atom_voltage_table_entry *voltage_table,
					 u16 *std_voltage_hi_sidd, u16 *std_voltage_lo_sidd)
{
	u16 v_index, idx;
	bool voltage_found = false;
	*std_voltage_hi_sidd = voltage_table->value * VOLTAGE_SCALE;
	*std_voltage_lo_sidd = voltage_table->value * VOLTAGE_SCALE;

	if (adev->pm.dpm.dyn_state.vddc_dependency_on_sclk.entries == NULL)
		return -EINVAL;

	if (adev->pm.dpm.dyn_state.cac_leakage_table.entries) {
		for (v_index = 0; (u32)v_index < adev->pm.dpm.dyn_state.vddc_dependency_on_sclk.count; v_index++) {
			if (voltage_table->value ==
			    adev->pm.dpm.dyn_state.vddc_dependency_on_sclk.entries[v_index].v) {
				voltage_found = true;
				if ((u32)v_index < adev->pm.dpm.dyn_state.cac_leakage_table.count)
					idx = v_index;
				else
					idx = adev->pm.dpm.dyn_state.cac_leakage_table.count - 1;
				*std_voltage_lo_sidd =
					adev->pm.dpm.dyn_state.cac_leakage_table.entries[idx].vddc * VOLTAGE_SCALE;
				*std_voltage_hi_sidd =
					adev->pm.dpm.dyn_state.cac_leakage_table.entries[idx].leakage * VOLTAGE_SCALE;
				break;
			}
		}

		if (!voltage_found) {
			for (v_index = 0; (u32)v_index < adev->pm.dpm.dyn_state.vddc_dependency_on_sclk.count; v_index++) {
				if (voltage_table->value <=
				    adev->pm.dpm.dyn_state.vddc_dependency_on_sclk.entries[v_index].v) {
					voltage_found = true;
					if ((u32)v_index < adev->pm.dpm.dyn_state.cac_leakage_table.count)
						idx = v_index;
					else
						idx = adev->pm.dpm.dyn_state.cac_leakage_table.count - 1;
					*std_voltage_lo_sidd =
						adev->pm.dpm.dyn_state.cac_leakage_table.entries[idx].vddc * VOLTAGE_SCALE;
					*std_voltage_hi_sidd =
						adev->pm.dpm.dyn_state.cac_leakage_table.entries[idx].leakage * VOLTAGE_SCALE;
					break;
				}
			}
		}
	}

	return 0;
}