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
struct amdgpu_device {int asic_type; } ;
typedef  enum amd_clockgating_state { ____Placeholder_amd_clockgating_state } amd_clockgating_state ;

/* Variables and functions */
 int AMD_CG_STATE_GATE ; 
#define  CHIP_FIJI 128 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  fiji_update_mc_light_sleep (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  fiji_update_mc_medium_grain_clock_gating (struct amdgpu_device*,int) ; 

__attribute__((used)) static int gmc_v8_0_set_clockgating_state(void *handle,
					  enum amd_clockgating_state state)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	if (amdgpu_sriov_vf(adev))
		return 0;

	switch (adev->asic_type) {
	case CHIP_FIJI:
		fiji_update_mc_medium_grain_clock_gating(adev,
				state == AMD_CG_STATE_GATE);
		fiji_update_mc_light_sleep(adev,
				state == AMD_CG_STATE_GATE);
		break;
	default:
		break;
	}
	return 0;
}