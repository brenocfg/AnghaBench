#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_4__ {size_t num_max_dpm_entries; TYPE_3__* entries; } ;
struct TYPE_5__ {TYPE_1__ sclk_voltage_mapping_table; } ;
struct sumo_power_info {TYPE_2__ sys_info; } ;
struct radeon_device {int dummy; } ;
struct TYPE_6__ {size_t sclk_frequency; } ;

/* Variables and functions */
 struct sumo_power_info* sumo_get_pi (struct radeon_device*) ; 

__attribute__((used)) static u32 sumo_get_valid_engine_clock(struct radeon_device *rdev,
				       u32 lower_limit)
{
	struct sumo_power_info *pi = sumo_get_pi(rdev);
	u32 i;

	for (i = 0; i < pi->sys_info.sclk_voltage_mapping_table.num_max_dpm_entries; i++) {
		if (pi->sys_info.sclk_voltage_mapping_table.entries[i].sclk_frequency >= lower_limit)
			return pi->sys_info.sclk_voltage_mapping_table.entries[i].sclk_frequency;
	}

	return pi->sys_info.sclk_voltage_mapping_table.entries[pi->sys_info.sclk_voltage_mapping_table.num_max_dpm_entries - 1].sclk_frequency;
}