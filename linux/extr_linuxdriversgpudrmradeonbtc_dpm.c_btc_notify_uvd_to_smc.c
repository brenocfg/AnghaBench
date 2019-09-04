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
struct radeon_ps {int /*<<< orphan*/  class2; int /*<<< orphan*/  class; } ;
struct radeon_device {int dummy; } ;
struct evergreen_power_info {int uvd_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  RV770_SMC_SOFT_REGISTER_uvd_enabled ; 
 struct evergreen_power_info* evergreen_get_pi (struct radeon_device*) ; 
 scalar_t__ r600_is_uvd_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rv770_write_smc_soft_register (struct radeon_device*,int /*<<< orphan*/ ,int) ; 

void btc_notify_uvd_to_smc(struct radeon_device *rdev,
			   struct radeon_ps *radeon_new_state)
{
	struct evergreen_power_info *eg_pi = evergreen_get_pi(rdev);

	if (r600_is_uvd_state(radeon_new_state->class, radeon_new_state->class2)) {
		rv770_write_smc_soft_register(rdev,
					      RV770_SMC_SOFT_REGISTER_uvd_enabled, 1);
		eg_pi->uvd_enabled = true;
	} else {
		rv770_write_smc_soft_register(rdev,
					      RV770_SMC_SOFT_REGISTER_uvd_enabled, 0);
		eg_pi->uvd_enabled = false;
	}
}