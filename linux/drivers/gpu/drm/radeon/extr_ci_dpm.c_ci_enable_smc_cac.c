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
struct radeon_device {int dummy; } ;
struct ci_power_info {int cac_enabled; scalar_t__ caps_cac; } ;
typedef  scalar_t__ PPSMC_Result ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PPSMC_MSG_DisableCac ; 
 int /*<<< orphan*/  PPSMC_MSG_EnableCac ; 
 scalar_t__ PPSMC_Result_OK ; 
 struct ci_power_info* ci_get_pi (struct radeon_device*) ; 
 scalar_t__ ci_send_msg_to_smc (struct radeon_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ci_enable_smc_cac(struct radeon_device *rdev, bool enable)
{
	struct ci_power_info *pi = ci_get_pi(rdev);
	PPSMC_Result smc_result;
	int ret = 0;

	if (pi->caps_cac) {
		if (enable) {
			smc_result = ci_send_msg_to_smc(rdev, PPSMC_MSG_EnableCac);
			if (smc_result != PPSMC_Result_OK) {
				ret = -EINVAL;
				pi->cac_enabled = false;
			} else {
				pi->cac_enabled = true;
			}
		} else if (pi->cac_enabled) {
			ci_send_msg_to_smc(rdev, PPSMC_MSG_DisableCac);
			pi->cac_enabled = false;
		}
	}

	return ret;
}