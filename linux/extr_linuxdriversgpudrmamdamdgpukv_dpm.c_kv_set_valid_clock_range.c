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
typedef  size_t u32 ;
struct sumo_sclk_voltage_mapping_table {TYPE_6__* entries; } ;
struct kv_ps {int num_levels; TYPE_7__* levels; } ;
struct TYPE_12__ {struct sumo_sclk_voltage_mapping_table sclk_voltage_mapping_table; } ;
struct kv_power_info {size_t graphics_dpm_level_count; size_t lowest_valid; size_t highest_valid; TYPE_5__ sys_info; } ;
struct amdgpu_ps {int dummy; } ;
struct amdgpu_clock_voltage_dependency_table {TYPE_4__* entries; scalar_t__ count; } ;
struct TYPE_8__ {struct amdgpu_clock_voltage_dependency_table vddc_dependency_on_sclk; } ;
struct TYPE_9__ {TYPE_1__ dyn_state; } ;
struct TYPE_10__ {TYPE_2__ dpm; } ;
struct amdgpu_device {TYPE_3__ pm; } ;
struct TYPE_14__ {scalar_t__ sclk; } ;
struct TYPE_13__ {scalar_t__ sclk_frequency; } ;
struct TYPE_11__ {scalar_t__ clk; } ;

/* Variables and functions */
 struct kv_power_info* kv_get_pi (struct amdgpu_device*) ; 
 struct kv_ps* kv_get_ps (struct amdgpu_ps*) ; 

__attribute__((used)) static void kv_set_valid_clock_range(struct amdgpu_device *adev,
				     struct amdgpu_ps *new_rps)
{
	struct kv_ps *new_ps = kv_get_ps(new_rps);
	struct kv_power_info *pi = kv_get_pi(adev);
	u32 i;
	struct amdgpu_clock_voltage_dependency_table *table =
		&adev->pm.dpm.dyn_state.vddc_dependency_on_sclk;

	if (table && table->count) {
		for (i = 0; i < pi->graphics_dpm_level_count; i++) {
			if ((table->entries[i].clk >= new_ps->levels[0].sclk) ||
			    (i == (pi->graphics_dpm_level_count - 1))) {
				pi->lowest_valid = i;
				break;
			}
		}

		for (i = pi->graphics_dpm_level_count - 1; i > 0; i--) {
			if (table->entries[i].clk <= new_ps->levels[new_ps->num_levels - 1].sclk)
				break;
		}
		pi->highest_valid = i;

		if (pi->lowest_valid > pi->highest_valid) {
			if ((new_ps->levels[0].sclk - table->entries[pi->highest_valid].clk) >
			    (table->entries[pi->lowest_valid].clk - new_ps->levels[new_ps->num_levels - 1].sclk))
				pi->highest_valid = pi->lowest_valid;
			else
				pi->lowest_valid =  pi->highest_valid;
		}
	} else {
		struct sumo_sclk_voltage_mapping_table *table =
			&pi->sys_info.sclk_voltage_mapping_table;

		for (i = 0; i < (int)pi->graphics_dpm_level_count; i++) {
			if (table->entries[i].sclk_frequency >= new_ps->levels[0].sclk ||
			    i == (int)(pi->graphics_dpm_level_count - 1)) {
				pi->lowest_valid = i;
				break;
			}
		}

		for (i = pi->graphics_dpm_level_count - 1; i > 0; i--) {
			if (table->entries[i].sclk_frequency <=
			    new_ps->levels[new_ps->num_levels - 1].sclk)
				break;
		}
		pi->highest_valid = i;

		if (pi->lowest_valid > pi->highest_valid) {
			if ((new_ps->levels[0].sclk -
			     table->entries[pi->highest_valid].sclk_frequency) >
			    (table->entries[pi->lowest_valid].sclk_frequency -
			     new_ps->levels[new_ps->num_levels -1].sclk))
				pi->highest_valid = pi->lowest_valid;
			else
				pi->lowest_valid =  pi->highest_valid;
		}
	}
}