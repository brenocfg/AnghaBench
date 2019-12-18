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
struct kv_power_info {int acp_power_gated; scalar_t__ caps_acp_pg; } ;
struct amdgpu_device {scalar_t__ asic_type; } ;

/* Variables and functions */
 scalar_t__ CHIP_KABINI ; 
 scalar_t__ CHIP_MULLINS ; 
 int /*<<< orphan*/  PPSMC_MSG_ACPPowerOFF ; 
 int /*<<< orphan*/  PPSMC_MSG_ACPPowerON ; 
 int /*<<< orphan*/  amdgpu_kv_notify_message_to_smu (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 struct kv_power_info* kv_get_pi (struct amdgpu_device*) ; 
 int /*<<< orphan*/  kv_update_acp_dpm (struct amdgpu_device*,int) ; 

__attribute__((used)) static void kv_dpm_powergate_acp(struct amdgpu_device *adev, bool gate)
{
	struct kv_power_info *pi = kv_get_pi(adev);

	if (pi->acp_power_gated == gate)
		return;

	if (adev->asic_type == CHIP_KABINI || adev->asic_type == CHIP_MULLINS)
		return;

	pi->acp_power_gated = gate;

	if (gate) {
		kv_update_acp_dpm(adev, true);
		if (pi->caps_acp_pg)
			amdgpu_kv_notify_message_to_smu(adev, PPSMC_MSG_ACPPowerOFF);
	} else {
		if (pi->caps_acp_pg)
			amdgpu_kv_notify_message_to_smu(adev, PPSMC_MSG_ACPPowerON);
		kv_update_acp_dpm(adev, false);
	}
}