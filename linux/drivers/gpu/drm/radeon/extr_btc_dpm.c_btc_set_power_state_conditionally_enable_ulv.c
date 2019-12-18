#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct radeon_ps {int dummy; } ;
struct radeon_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ supported; } ;
struct evergreen_power_info {TYPE_1__ ulv; } ;

/* Variables and functions */
 int btc_enable_ulv (struct radeon_device*) ; 
 scalar_t__ btc_is_state_ulv_compatible (struct radeon_device*,struct radeon_ps*) ; 
 int btc_set_ulv_dram_timing (struct radeon_device*) ; 
 struct evergreen_power_info* evergreen_get_pi (struct radeon_device*) ; 

__attribute__((used)) static int btc_set_power_state_conditionally_enable_ulv(struct radeon_device *rdev,
							struct radeon_ps *radeon_new_state)
{
	int ret = 0;
	struct evergreen_power_info *eg_pi = evergreen_get_pi(rdev);

	if (eg_pi->ulv.supported) {
		if (btc_is_state_ulv_compatible(rdev, radeon_new_state)) {
			// Set ARB[0] to reflect the DRAM timing needed for ULV.
			ret = btc_set_ulv_dram_timing(rdev);
			if (ret == 0)
				ret = btc_enable_ulv(rdev);
		}
	}

	return ret;
}