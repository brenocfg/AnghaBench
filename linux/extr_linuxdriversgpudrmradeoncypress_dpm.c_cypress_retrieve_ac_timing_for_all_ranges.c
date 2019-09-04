#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct radeon_device {int dummy; } ;
struct TYPE_3__ {size_t num_entries; int valid_flag; size_t last; TYPE_2__* mc_reg_table_entry; } ;
struct evergreen_power_info {TYPE_1__ mc_reg_table; } ;
struct atom_memory_clock_range_table {size_t num_entries; int /*<<< orphan*/ * mclk; } ;
struct TYPE_4__ {scalar_t__* mc_data; int /*<<< orphan*/  mclk_max; } ;

/* Variables and functions */
 int /*<<< orphan*/  cypress_retrieve_ac_timing_for_one_entry (struct radeon_device*,TYPE_2__*) ; 
 struct evergreen_power_info* evergreen_get_pi (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_atom_set_ac_timing (struct radeon_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cypress_retrieve_ac_timing_for_all_ranges(struct radeon_device *rdev,
						      struct atom_memory_clock_range_table *range_table)
{
	struct evergreen_power_info *eg_pi = evergreen_get_pi(rdev);
	u32 i, j;

	for (i = 0; i < range_table->num_entries; i++) {
		eg_pi->mc_reg_table.mc_reg_table_entry[i].mclk_max =
			range_table->mclk[i];
		radeon_atom_set_ac_timing(rdev, range_table->mclk[i]);
		cypress_retrieve_ac_timing_for_one_entry(rdev,
							 &eg_pi->mc_reg_table.mc_reg_table_entry[i]);
	}

	eg_pi->mc_reg_table.num_entries = range_table->num_entries;
	eg_pi->mc_reg_table.valid_flag = 0;

	for (i = 0; i < eg_pi->mc_reg_table.last; i++) {
		for (j = 1; j < range_table->num_entries; j++) {
			if (eg_pi->mc_reg_table.mc_reg_table_entry[j-1].mc_data[i] !=
			    eg_pi->mc_reg_table.mc_reg_table_entry[j].mc_data[i]) {
				eg_pi->mc_reg_table.valid_flag |= (1 << i);
				break;
			}
		}
	}
}