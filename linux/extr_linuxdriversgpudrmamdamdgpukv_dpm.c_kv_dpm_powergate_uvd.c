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
struct kv_power_info {int uvd_power_gated; scalar_t__ caps_uvd_pg; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_IP_BLOCK_TYPE_UVD ; 
 int /*<<< orphan*/  AMD_PG_STATE_GATE ; 
 int /*<<< orphan*/  AMD_PG_STATE_UNGATE ; 
 int /*<<< orphan*/  PPSMC_MSG_UVDPowerOFF ; 
 int /*<<< orphan*/  PPSMC_MSG_UVDPowerON ; 
 int amdgpu_device_ip_set_powergating_state (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_kv_notify_message_to_smu (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 struct kv_power_info* kv_get_pi (struct amdgpu_device*) ; 
 int /*<<< orphan*/  kv_update_uvd_dpm (struct amdgpu_device*,int) ; 

__attribute__((used)) static void kv_dpm_powergate_uvd(void *handle, bool gate)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	struct kv_power_info *pi = kv_get_pi(adev);
	int ret;

	pi->uvd_power_gated = gate;

	if (gate) {
		/* stop the UVD block */
		ret = amdgpu_device_ip_set_powergating_state(adev, AMD_IP_BLOCK_TYPE_UVD,
							     AMD_PG_STATE_GATE);
		kv_update_uvd_dpm(adev, gate);
		if (pi->caps_uvd_pg)
			/* power off the UVD block */
			amdgpu_kv_notify_message_to_smu(adev, PPSMC_MSG_UVDPowerOFF);
	} else {
		if (pi->caps_uvd_pg)
			/* power on the UVD block */
			amdgpu_kv_notify_message_to_smu(adev, PPSMC_MSG_UVDPowerON);
			/* re-init the UVD block */
		kv_update_uvd_dpm(adev, gate);

		ret = amdgpu_device_ip_set_powergating_state(adev, AMD_IP_BLOCK_TYPE_UVD,
							     AMD_PG_STATE_UNGATE);
	}
}