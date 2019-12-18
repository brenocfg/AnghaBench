#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  size_t u16 ;
struct TYPE_13__ {scalar_t__ count; TYPE_3__* entries; } ;
struct TYPE_11__ {scalar_t__ count; TYPE_1__* entries; } ;
struct TYPE_14__ {TYPE_4__ cac_leakage_table; TYPE_2__ vddc_dependency_on_sclk; } ;
struct TYPE_15__ {int platform_caps; TYPE_5__ dyn_state; } ;
struct TYPE_16__ {TYPE_6__ dpm; } ;
struct amdgpu_device {TYPE_7__ pm; } ;
struct TYPE_17__ {size_t index; int /*<<< orphan*/  value; } ;
struct TYPE_12__ {size_t vddc; } ;
struct TYPE_10__ {scalar_t__ v; } ;
typedef  TYPE_8__ SISLANDS_SMC_VOLTAGE_VALUE ;

/* Variables and functions */
 int ATOM_PP_PLATFORM_CAP_NEW_CAC_VOLTAGE ; 
 int EINVAL ; 
 size_t be16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int si_get_std_voltage_value(struct amdgpu_device *adev,
				    SISLANDS_SMC_VOLTAGE_VALUE *voltage,
				    u16 *std_voltage)
{
	u16 v_index;
	bool voltage_found = false;
	*std_voltage = be16_to_cpu(voltage->value);

	if (adev->pm.dpm.dyn_state.cac_leakage_table.entries) {
		if (adev->pm.dpm.platform_caps & ATOM_PP_PLATFORM_CAP_NEW_CAC_VOLTAGE) {
			if (adev->pm.dpm.dyn_state.vddc_dependency_on_sclk.entries == NULL)
				return -EINVAL;

			for (v_index = 0; (u32)v_index < adev->pm.dpm.dyn_state.vddc_dependency_on_sclk.count; v_index++) {
				if (be16_to_cpu(voltage->value) ==
				    (u16)adev->pm.dpm.dyn_state.vddc_dependency_on_sclk.entries[v_index].v) {
					voltage_found = true;
					if ((u32)v_index < adev->pm.dpm.dyn_state.cac_leakage_table.count)
						*std_voltage =
							adev->pm.dpm.dyn_state.cac_leakage_table.entries[v_index].vddc;
					else
						*std_voltage =
							adev->pm.dpm.dyn_state.cac_leakage_table.entries[adev->pm.dpm.dyn_state.cac_leakage_table.count-1].vddc;
					break;
				}
			}

			if (!voltage_found) {
				for (v_index = 0; (u32)v_index < adev->pm.dpm.dyn_state.vddc_dependency_on_sclk.count; v_index++) {
					if (be16_to_cpu(voltage->value) <=
					    (u16)adev->pm.dpm.dyn_state.vddc_dependency_on_sclk.entries[v_index].v) {
						voltage_found = true;
						if ((u32)v_index < adev->pm.dpm.dyn_state.cac_leakage_table.count)
							*std_voltage =
								adev->pm.dpm.dyn_state.cac_leakage_table.entries[v_index].vddc;
						else
							*std_voltage =
								adev->pm.dpm.dyn_state.cac_leakage_table.entries[adev->pm.dpm.dyn_state.cac_leakage_table.count-1].vddc;
						break;
					}
				}
			}
		} else {
			if ((u32)voltage->index < adev->pm.dpm.dyn_state.cac_leakage_table.count)
				*std_voltage = adev->pm.dpm.dyn_state.cac_leakage_table.entries[voltage->index].vddc;
		}
	}

	return 0;
}