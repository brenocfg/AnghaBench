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
struct kv_power_info {int samu_power_gated; scalar_t__ caps_samu_pg; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPSMC_MSG_SAMPowerOFF ; 
 int /*<<< orphan*/  PPSMC_MSG_SAMPowerON ; 
 struct kv_power_info* kv_get_pi (struct radeon_device*) ; 
 int /*<<< orphan*/  kv_notify_message_to_smu (struct radeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kv_update_samu_dpm (struct radeon_device*,int) ; 

__attribute__((used)) static void kv_dpm_powergate_samu(struct radeon_device *rdev, bool gate)
{
	struct kv_power_info *pi = kv_get_pi(rdev);

	if (pi->samu_power_gated == gate)
		return;

	pi->samu_power_gated = gate;

	if (gate) {
		kv_update_samu_dpm(rdev, true);
		if (pi->caps_samu_pg)
			kv_notify_message_to_smu(rdev, PPSMC_MSG_SAMPowerOFF);
	} else {
		if (pi->caps_samu_pg)
			kv_notify_message_to_smu(rdev, PPSMC_MSG_SAMPowerON);
		kv_update_samu_dpm(rdev, false);
	}
}