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
typedef  int u8 ;
struct kv_power_info {int acp_boot_level; int /*<<< orphan*/  caps_stable_p_state; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPSMC_MSG_ACPDPM_SetEnabledMask ; 
 int /*<<< orphan*/  amdgpu_kv_send_msg_to_smc_with_parameter (struct amdgpu_device*,int /*<<< orphan*/ ,int) ; 
 int kv_get_acp_boot_level (struct amdgpu_device*) ; 
 struct kv_power_info* kv_get_pi (struct amdgpu_device*) ; 

__attribute__((used)) static void kv_update_acp_boot_level(struct amdgpu_device *adev)
{
	struct kv_power_info *pi = kv_get_pi(adev);
	u8 acp_boot_level;

	if (!pi->caps_stable_p_state) {
		acp_boot_level = kv_get_acp_boot_level(adev);
		if (acp_boot_level != pi->acp_boot_level) {
			pi->acp_boot_level = acp_boot_level;
			amdgpu_kv_send_msg_to_smc_with_parameter(adev,
							  PPSMC_MSG_ACPDPM_SetEnabledMask,
							  (1 << pi->acp_boot_level));
		}
	}
}