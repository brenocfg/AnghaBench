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
struct ni_power_info {int support_cac_long_term_average; int cac_enabled; scalar_t__ enable_cac; } ;
typedef  scalar_t__ PPSMC_Result ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PPSMC_CACLongTermAvgDisable ; 
 int /*<<< orphan*/  PPSMC_CACLongTermAvgEnable ; 
 int /*<<< orphan*/  PPSMC_MSG_CollectCAC_PowerCorreln ; 
 int /*<<< orphan*/  PPSMC_MSG_DisableCac ; 
 int /*<<< orphan*/  PPSMC_MSG_EnableCac ; 
 scalar_t__ PPSMC_Result_OK ; 
 struct ni_power_info* ni_get_pi (struct radeon_device*) ; 
 int /*<<< orphan*/  r600_is_uvd_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rv770_send_msg_to_smc (struct radeon_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ni_enable_smc_cac(struct radeon_device *rdev,
			     struct radeon_ps *radeon_new_state,
			     bool enable)
{
	struct ni_power_info *ni_pi = ni_get_pi(rdev);
	int ret = 0;
	PPSMC_Result smc_result;

	if (ni_pi->enable_cac) {
		if (enable) {
			if (!r600_is_uvd_state(radeon_new_state->class, radeon_new_state->class2)) {
				smc_result = rv770_send_msg_to_smc(rdev, PPSMC_MSG_CollectCAC_PowerCorreln);

				if (ni_pi->support_cac_long_term_average) {
					smc_result = rv770_send_msg_to_smc(rdev, PPSMC_CACLongTermAvgEnable);
					if (PPSMC_Result_OK != smc_result)
						ni_pi->support_cac_long_term_average = false;
				}

				smc_result = rv770_send_msg_to_smc(rdev, PPSMC_MSG_EnableCac);
				if (PPSMC_Result_OK != smc_result)
					ret = -EINVAL;

				ni_pi->cac_enabled = (PPSMC_Result_OK == smc_result) ? true : false;
			}
		} else if (ni_pi->cac_enabled) {
			smc_result = rv770_send_msg_to_smc(rdev, PPSMC_MSG_DisableCac);

			ni_pi->cac_enabled = false;

			if (ni_pi->support_cac_long_term_average) {
				smc_result = rv770_send_msg_to_smc(rdev, PPSMC_CACLongTermAvgDisable);
				if (PPSMC_Result_OK != smc_result)
					ni_pi->support_cac_long_term_average = false;
			}
		}
	}

	return ret;
}