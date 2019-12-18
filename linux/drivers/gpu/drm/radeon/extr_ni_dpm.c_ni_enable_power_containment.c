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
struct ni_power_info {int pc_enabled; scalar_t__ enable_power_containment; } ;
typedef  scalar_t__ PPSMC_Result ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PPSMC_Result_OK ; 
 int /*<<< orphan*/  PPSMC_TDPClampingActive ; 
 int /*<<< orphan*/  PPSMC_TDPClampingInactive ; 
 struct ni_power_info* ni_get_pi (struct radeon_device*) ; 
 int /*<<< orphan*/  r600_is_uvd_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rv770_send_msg_to_smc (struct radeon_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ni_enable_power_containment(struct radeon_device *rdev,
				       struct radeon_ps *radeon_new_state,
				       bool enable)
{
	struct ni_power_info *ni_pi = ni_get_pi(rdev);
	PPSMC_Result smc_result;
	int ret = 0;

	if (ni_pi->enable_power_containment) {
		if (enable) {
			if (!r600_is_uvd_state(radeon_new_state->class, radeon_new_state->class2)) {
				smc_result = rv770_send_msg_to_smc(rdev, PPSMC_TDPClampingActive);
				if (smc_result != PPSMC_Result_OK) {
					ret = -EINVAL;
					ni_pi->pc_enabled = false;
				} else {
					ni_pi->pc_enabled = true;
				}
			}
		} else {
			smc_result = rv770_send_msg_to_smc(rdev, PPSMC_TDPClampingInactive);
			if (smc_result != PPSMC_Result_OK)
				ret = -EINVAL;
			ni_pi->pc_enabled = false;
		}
	}

	return ret;
}