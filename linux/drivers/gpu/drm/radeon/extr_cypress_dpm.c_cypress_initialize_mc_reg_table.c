#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct rv7xx_power_info {int /*<<< orphan*/  mem_gddr5; } ;
struct radeon_device {int dummy; } ;
struct atom_memory_clock_range_table {int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  cypress_retrieve_ac_timing_for_all_ranges (struct radeon_device*,struct atom_memory_clock_range_table*) ; 
 int radeon_atom_get_mclk_range_table (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct atom_memory_clock_range_table*) ; 
 int /*<<< orphan*/  rv770_get_memory_module_index (struct radeon_device*) ; 
 struct rv7xx_power_info* rv770_get_pi (struct radeon_device*) ; 

__attribute__((used)) static int cypress_initialize_mc_reg_table(struct radeon_device *rdev)
{
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);
	u8 module_index = rv770_get_memory_module_index(rdev);
	struct atom_memory_clock_range_table range_table = { 0 };
	int ret;

	ret = radeon_atom_get_mclk_range_table(rdev,
					       pi->mem_gddr5,
					       module_index, &range_table);
	if (ret)
		return ret;

	cypress_retrieve_ac_timing_for_all_ranges(rdev, &range_table);

	return 0;
}