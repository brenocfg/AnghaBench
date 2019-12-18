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
struct radeon_clock_voltage_dependency_table {TYPE_4__* entries; scalar_t__ count; } ;
struct TYPE_8__ {struct radeon_clock_voltage_dependency_table vddc_dependency_on_sclk; } ;
struct TYPE_9__ {TYPE_1__ dyn_state; } ;
struct TYPE_10__ {TYPE_2__ dpm; } ;
struct radeon_device {TYPE_3__ pm; } ;
struct TYPE_12__ {struct sumo_sclk_voltage_mapping_table sclk_voltage_mapping_table; } ;
struct kv_power_info {size_t graphics_dpm_level_count; TYPE_7__* graphics_level; scalar_t__ caps_enable_dfs_bypass; TYPE_5__ sys_info; } ;
struct TYPE_14__ {int ClkBypassCntl; } ;
struct TYPE_13__ {int /*<<< orphan*/  sclk_frequency; } ;
struct TYPE_11__ {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int kv_get_clock_difference (int /*<<< orphan*/ ,int) ; 
 struct kv_power_info* kv_get_pi (struct radeon_device*) ; 

__attribute__((used)) static void kv_calculate_dfs_bypass_settings(struct radeon_device *rdev)
{
	struct kv_power_info *pi = kv_get_pi(rdev);
	u32 i;
	struct radeon_clock_voltage_dependency_table *table =
		&rdev->pm.dpm.dyn_state.vddc_dependency_on_sclk;

	if (table && table->count) {
		for (i = 0; i < pi->graphics_dpm_level_count; i++) {
			if (pi->caps_enable_dfs_bypass) {
				if (kv_get_clock_difference(table->entries[i].clk, 40000) < 200)
					pi->graphics_level[i].ClkBypassCntl = 3;
				else if (kv_get_clock_difference(table->entries[i].clk, 30000) < 200)
					pi->graphics_level[i].ClkBypassCntl = 2;
				else if (kv_get_clock_difference(table->entries[i].clk, 26600) < 200)
					pi->graphics_level[i].ClkBypassCntl = 7;
				else if (kv_get_clock_difference(table->entries[i].clk , 20000) < 200)
					pi->graphics_level[i].ClkBypassCntl = 6;
				else if (kv_get_clock_difference(table->entries[i].clk , 10000) < 200)
					pi->graphics_level[i].ClkBypassCntl = 8;
				else
					pi->graphics_level[i].ClkBypassCntl = 0;
			} else {
				pi->graphics_level[i].ClkBypassCntl = 0;
			}
		}
	} else {
		struct sumo_sclk_voltage_mapping_table *table =
			&pi->sys_info.sclk_voltage_mapping_table;
		for (i = 0; i < pi->graphics_dpm_level_count; i++) {
			if (pi->caps_enable_dfs_bypass) {
				if (kv_get_clock_difference(table->entries[i].sclk_frequency, 40000) < 200)
					pi->graphics_level[i].ClkBypassCntl = 3;
				else if (kv_get_clock_difference(table->entries[i].sclk_frequency, 30000) < 200)
					pi->graphics_level[i].ClkBypassCntl = 2;
				else if (kv_get_clock_difference(table->entries[i].sclk_frequency, 26600) < 200)
					pi->graphics_level[i].ClkBypassCntl = 7;
				else if (kv_get_clock_difference(table->entries[i].sclk_frequency, 20000) < 200)
					pi->graphics_level[i].ClkBypassCntl = 6;
				else if (kv_get_clock_difference(table->entries[i].sclk_frequency, 10000) < 200)
					pi->graphics_level[i].ClkBypassCntl = 8;
				else
					pi->graphics_level[i].ClkBypassCntl = 0;
			} else {
				pi->graphics_level[i].ClkBypassCntl = 0;
			}
		}
	}
}