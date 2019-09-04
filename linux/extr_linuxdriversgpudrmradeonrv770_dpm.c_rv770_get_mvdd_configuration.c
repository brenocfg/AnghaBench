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
struct rv7xx_power_info {int mvdd_control; scalar_t__ mvdd_split_frequency; } ;
struct radeon_device {int dummy; } ;
struct atom_memory_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ radeon_atom_get_memory_info (struct radeon_device*,int /*<<< orphan*/ ,struct atom_memory_info*) ; 
 scalar_t__ rv770_get_mclk_split_point (struct atom_memory_info*) ; 
 int /*<<< orphan*/  rv770_get_memory_module_index (struct radeon_device*) ; 
 int rv770_get_mvdd_pin_configuration (struct radeon_device*) ; 
 struct rv7xx_power_info* rv770_get_pi (struct radeon_device*) ; 

__attribute__((used)) static int rv770_get_mvdd_configuration(struct radeon_device *rdev)
{
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);
	u8 memory_module_index;
	struct atom_memory_info memory_info;

	memory_module_index = rv770_get_memory_module_index(rdev);

	if (radeon_atom_get_memory_info(rdev, memory_module_index, &memory_info)) {
		pi->mvdd_control = false;
		return 0;
	}

	pi->mvdd_split_frequency =
		rv770_get_mclk_split_point(&memory_info);

	if (pi->mvdd_split_frequency == 0) {
		pi->mvdd_control = false;
		return 0;
	}

	return rv770_get_mvdd_pin_configuration(rdev);
}