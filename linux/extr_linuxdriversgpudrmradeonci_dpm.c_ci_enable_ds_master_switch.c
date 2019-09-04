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
struct ci_power_info {scalar_t__ caps_sclk_ds; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PPSMC_MSG_MASTER_DeepSleep_OFF ; 
 int /*<<< orphan*/  PPSMC_MSG_MASTER_DeepSleep_ON ; 
 scalar_t__ PPSMC_Result_OK ; 
 struct ci_power_info* ci_get_pi (struct radeon_device*) ; 
 scalar_t__ ci_send_msg_to_smc (struct radeon_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ci_enable_ds_master_switch(struct radeon_device *rdev,
				      bool enable)
{
	struct ci_power_info *pi = ci_get_pi(rdev);

	if (enable) {
		if (pi->caps_sclk_ds) {
			if (ci_send_msg_to_smc(rdev, PPSMC_MSG_MASTER_DeepSleep_ON) != PPSMC_Result_OK)
				return -EINVAL;
		} else {
			if (ci_send_msg_to_smc(rdev, PPSMC_MSG_MASTER_DeepSleep_OFF) != PPSMC_Result_OK)
				return -EINVAL;
		}
	} else {
		if (pi->caps_sclk_ds) {
			if (ci_send_msg_to_smc(rdev, PPSMC_MSG_MASTER_DeepSleep_OFF) != PPSMC_Result_OK)
				return -EINVAL;
		}
	}

	return 0;
}