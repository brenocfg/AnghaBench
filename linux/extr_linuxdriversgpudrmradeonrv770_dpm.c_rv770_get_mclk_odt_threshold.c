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
struct rv7xx_power_info {int mclk_odt_threshold; } ;
struct radeon_device {scalar_t__ family; } ;
struct atom_memory_info {scalar_t__ mem_type; } ;

/* Variables and functions */
 scalar_t__ CHIP_RV710 ; 
 scalar_t__ CHIP_RV730 ; 
 scalar_t__ MEM_TYPE_DDR2 ; 
 scalar_t__ MEM_TYPE_DDR3 ; 
 scalar_t__ radeon_atom_get_memory_info (struct radeon_device*,int /*<<< orphan*/ ,struct atom_memory_info*) ; 
 int /*<<< orphan*/  rv770_get_memory_module_index (struct radeon_device*) ; 
 struct rv7xx_power_info* rv770_get_pi (struct radeon_device*) ; 

__attribute__((used)) static void rv770_get_mclk_odt_threshold(struct radeon_device *rdev)
{
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);
	u8 memory_module_index;
	struct atom_memory_info memory_info;

	pi->mclk_odt_threshold = 0;

	if ((rdev->family == CHIP_RV730) || (rdev->family == CHIP_RV710)) {
		memory_module_index = rv770_get_memory_module_index(rdev);

		if (radeon_atom_get_memory_info(rdev, memory_module_index, &memory_info))
			return;

		if (memory_info.mem_type == MEM_TYPE_DDR2 ||
		    memory_info.mem_type == MEM_TYPE_DDR3)
			pi->mclk_odt_threshold = 30000;
	}
}