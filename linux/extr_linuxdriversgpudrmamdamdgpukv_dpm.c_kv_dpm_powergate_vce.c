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
struct kv_power_info {int vce_power_gated; scalar_t__ caps_vce_pg; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_IP_BLOCK_TYPE_VCE ; 
 int /*<<< orphan*/  AMD_PG_STATE_GATE ; 
 int /*<<< orphan*/  AMD_PG_STATE_UNGATE ; 
 int /*<<< orphan*/  PPSMC_MSG_VCEPowerOFF ; 
 int /*<<< orphan*/  PPSMC_MSG_VCEPowerON ; 
 int amdgpu_device_ip_set_powergating_state (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_kv_notify_message_to_smu (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kv_enable_vce_dpm (struct amdgpu_device*,int) ; 
 struct kv_power_info* kv_get_pi (struct amdgpu_device*) ; 

__attribute__((used)) static void kv_dpm_powergate_vce(void *handle, bool gate)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	struct kv_power_info *pi = kv_get_pi(adev);
	int ret;

	pi->vce_power_gated = gate;

	if (gate) {
		/* stop the VCE block */
		ret = amdgpu_device_ip_set_powergating_state(adev, AMD_IP_BLOCK_TYPE_VCE,
							     AMD_PG_STATE_GATE);
		kv_enable_vce_dpm(adev, false);
		if (pi->caps_vce_pg) /* power off the VCE block */
			amdgpu_kv_notify_message_to_smu(adev, PPSMC_MSG_VCEPowerOFF);
	} else {
		if (pi->caps_vce_pg) /* power on the VCE block */
			amdgpu_kv_notify_message_to_smu(adev, PPSMC_MSG_VCEPowerON);
		kv_enable_vce_dpm(adev, true);
		/* re-init the VCE block */
		ret = amdgpu_device_ip_set_powergating_state(adev, AMD_IP_BLOCK_TYPE_VCE,
							     AMD_PG_STATE_UNGATE);
	}
}