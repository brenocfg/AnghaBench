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
struct radeon_device {int dummy; } ;
struct radeon_clock_and_voltage_limits {int /*<<< orphan*/  mclk; int /*<<< orphan*/  vddc; int /*<<< orphan*/  sclk; } ;
struct TYPE_6__ {int num_max_dpm_entries; TYPE_1__* entries; } ;
struct TYPE_5__ {int /*<<< orphan*/ * nbp_memory_clock; TYPE_3__ sclk_voltage_mapping_table; } ;
struct kv_power_info {TYPE_2__ sys_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  vid_2bit; int /*<<< orphan*/  sclk_frequency; } ;

/* Variables and functions */
 int /*<<< orphan*/  kv_convert_2bit_index_to_voltage (struct radeon_device*,int /*<<< orphan*/ ) ; 
 struct kv_power_info* kv_get_pi (struct radeon_device*) ; 

__attribute__((used)) static void kv_construct_max_power_limits_table(struct radeon_device *rdev,
						struct radeon_clock_and_voltage_limits *table)
{
	struct kv_power_info *pi = kv_get_pi(rdev);

	if (pi->sys_info.sclk_voltage_mapping_table.num_max_dpm_entries > 0) {
		int idx = pi->sys_info.sclk_voltage_mapping_table.num_max_dpm_entries - 1;
		table->sclk =
			pi->sys_info.sclk_voltage_mapping_table.entries[idx].sclk_frequency;
		table->vddc =
			kv_convert_2bit_index_to_voltage(rdev,
							 pi->sys_info.sclk_voltage_mapping_table.entries[idx].vid_2bit);
	}

	table->mclk = pi->sys_info.nbp_memory_clock[0];
}