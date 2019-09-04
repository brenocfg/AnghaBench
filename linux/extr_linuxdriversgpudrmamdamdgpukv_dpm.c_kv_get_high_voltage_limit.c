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
struct sumo_sclk_voltage_mapping_table {int num_max_dpm_entries; TYPE_6__* entries; } ;
struct TYPE_11__ {struct sumo_sclk_voltage_mapping_table sclk_voltage_mapping_table; } ;
struct kv_power_info {scalar_t__ high_voltage_t; TYPE_5__ sys_info; } ;
struct amdgpu_clock_voltage_dependency_table {int count; TYPE_4__* entries; } ;
struct TYPE_7__ {struct amdgpu_clock_voltage_dependency_table vddc_dependency_on_sclk; } ;
struct TYPE_8__ {TYPE_1__ dyn_state; } ;
struct TYPE_9__ {TYPE_2__ dpm; } ;
struct amdgpu_device {TYPE_3__ pm; } ;
struct TYPE_12__ {int /*<<< orphan*/  vid_2bit; } ;
struct TYPE_10__ {int /*<<< orphan*/  v; } ;

/* Variables and functions */
 scalar_t__ kv_convert_2bit_index_to_voltage (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ kv_convert_8bit_index_to_voltage (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 struct kv_power_info* kv_get_pi (struct amdgpu_device*) ; 

__attribute__((used)) static int kv_get_high_voltage_limit(struct amdgpu_device *adev, int *limit)
{
	struct kv_power_info *pi = kv_get_pi(adev);
	struct amdgpu_clock_voltage_dependency_table *table =
		&adev->pm.dpm.dyn_state.vddc_dependency_on_sclk;
	int i;

	if (table && table->count) {
		for (i = table->count - 1; i >= 0; i--) {
			if (pi->high_voltage_t &&
			    (kv_convert_8bit_index_to_voltage(adev, table->entries[i].v) <=
			     pi->high_voltage_t)) {
				*limit = i;
				return 0;
			}
		}
	} else {
		struct sumo_sclk_voltage_mapping_table *table =
			&pi->sys_info.sclk_voltage_mapping_table;

		for (i = table->num_max_dpm_entries - 1; i >= 0; i--) {
			if (pi->high_voltage_t &&
			    (kv_convert_2bit_index_to_voltage(adev, table->entries[i].vid_2bit) <=
			     pi->high_voltage_t)) {
				*limit = i;
				return 0;
			}
		}
	}

	*limit = 0;
	return 0;
}