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
typedef  int u32 ;
struct rv7xx_power_info {int mvdd_control; scalar_t__ mvdd_split_frequency; } ;
struct radeon_device {int dummy; } ;
struct evergreen_power_info {int mvdd_high_index; int mvdd_low_index; } ;
struct atom_memory_info {int dummy; } ;

/* Variables and functions */
 int BACKBIAS_PAD_EN ; 
 int BACKBIAS_VALUE ; 
 int /*<<< orphan*/  GENERAL_PWRMGT ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 scalar_t__ cypress_get_mclk_split_point (struct atom_memory_info*) ; 
 struct evergreen_power_info* evergreen_get_pi (struct radeon_device*) ; 
 scalar_t__ radeon_atom_get_memory_info (struct radeon_device*,int /*<<< orphan*/ ,struct atom_memory_info*) ; 
 int /*<<< orphan*/  rv770_get_memory_module_index (struct radeon_device*) ; 
 struct rv7xx_power_info* rv770_get_pi (struct radeon_device*) ; 

int cypress_get_mvdd_configuration(struct radeon_device *rdev)
{
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);
	struct evergreen_power_info *eg_pi = evergreen_get_pi(rdev);
	u8 module_index;
	struct atom_memory_info memory_info;
	u32 tmp = RREG32(GENERAL_PWRMGT);

	if (!(tmp & BACKBIAS_PAD_EN)) {
		eg_pi->mvdd_high_index = 0;
		eg_pi->mvdd_low_index = 1;
		pi->mvdd_control = false;
		return 0;
	}

	if (tmp & BACKBIAS_VALUE)
		eg_pi->mvdd_high_index = 1;
	else
		eg_pi->mvdd_high_index = 0;

	eg_pi->mvdd_low_index =
		(eg_pi->mvdd_high_index == 0) ? 1 : 0;

	module_index = rv770_get_memory_module_index(rdev);

	if (radeon_atom_get_memory_info(rdev, module_index, &memory_info)) {
		pi->mvdd_control = false;
		return 0;
	}

	pi->mvdd_split_frequency =
		cypress_get_mclk_split_point(&memory_info);

	if (pi->mvdd_split_frequency == 0) {
		pi->mvdd_control = false;
		return 0;
	}

	return 0;
}