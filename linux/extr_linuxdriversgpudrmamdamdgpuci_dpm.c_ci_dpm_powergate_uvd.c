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
struct ci_power_info {int uvd_power_gated; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_IP_BLOCK_TYPE_UVD ; 
 int /*<<< orphan*/  AMD_PG_STATE_GATE ; 
 int /*<<< orphan*/  AMD_PG_STATE_UNGATE ; 
 int /*<<< orphan*/  amdgpu_device_ip_set_powergating_state (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ci_power_info* ci_get_pi (struct amdgpu_device*) ; 
 int /*<<< orphan*/  ci_update_uvd_dpm (struct amdgpu_device*,int) ; 

__attribute__((used)) static void ci_dpm_powergate_uvd(void *handle, bool gate)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	struct ci_power_info *pi = ci_get_pi(adev);

	pi->uvd_power_gated = gate;

	if (gate) {
		/* stop the UVD block */
		amdgpu_device_ip_set_powergating_state(adev, AMD_IP_BLOCK_TYPE_UVD,
						       AMD_PG_STATE_GATE);
		ci_update_uvd_dpm(adev, gate);
	} else {
		amdgpu_device_ip_set_powergating_state(adev, AMD_IP_BLOCK_TYPE_UVD,
						       AMD_PG_STATE_UNGATE);
		ci_update_uvd_dpm(adev, gate);
	}
}