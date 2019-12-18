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
struct kv_power_info {int cac_enabled; scalar_t__ caps_cac; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPSMC_MSG_DisableCac ; 
 int /*<<< orphan*/  PPSMC_MSG_EnableCac ; 
 struct kv_power_info* kv_get_pi (struct radeon_device*) ; 
 int kv_notify_message_to_smu (struct radeon_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kv_enable_smc_cac(struct radeon_device *rdev, bool enable)
{
	struct kv_power_info *pi = kv_get_pi(rdev);
	int ret = 0;

	if (pi->caps_cac) {
		if (enable) {
			ret = kv_notify_message_to_smu(rdev, PPSMC_MSG_EnableCac);
			if (ret)
				pi->cac_enabled = false;
			else
				pi->cac_enabled = true;
		} else if (pi->cac_enabled) {
			kv_notify_message_to_smu(rdev, PPSMC_MSG_DisableCac);
			pi->cac_enabled = false;
		}
	}

	return ret;
}