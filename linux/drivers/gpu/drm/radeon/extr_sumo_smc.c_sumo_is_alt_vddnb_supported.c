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
struct sumo_power_info {int fw_version; int /*<<< orphan*/  enable_alt_vddnb; } ;
struct radeon_device {scalar_t__ family; } ;

/* Variables and functions */
 scalar_t__ CHIP_SUMO ; 
 scalar_t__ CHIP_SUMO2 ; 
 struct sumo_power_info* sumo_get_pi (struct radeon_device*) ; 

__attribute__((used)) static bool sumo_is_alt_vddnb_supported(struct radeon_device *rdev)
{
	struct sumo_power_info *pi = sumo_get_pi(rdev);
	bool return_code = false;

	if (!pi->enable_alt_vddnb)
		return return_code;

	if ((rdev->family == CHIP_SUMO) || (rdev->family == CHIP_SUMO2)) {
		if (pi->fw_version >= 0x00010C00)
			return_code = true;
	}

	return return_code;
}