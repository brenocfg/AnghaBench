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
struct amdgpu_device {int dummy; } ;
typedef  enum amd_clockgating_state { ____Placeholder_amd_clockgating_state } amd_clockgating_state ;

/* Variables and functions */
 int AMD_CG_STATE_GATE ; 
 int EBUSY ; 
 int /*<<< orphan*/  uvd_v5_0_enable_clock_gating (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  uvd_v5_0_set_sw_clock_gating (struct amdgpu_device*) ; 
 scalar_t__ uvd_v5_0_wait_for_idle (void*) ; 

__attribute__((used)) static int uvd_v5_0_set_clockgating_state(void *handle,
					  enum amd_clockgating_state state)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	bool enable = (state == AMD_CG_STATE_GATE) ? true : false;

	if (enable) {
		/* wait for STATUS to clear */
		if (uvd_v5_0_wait_for_idle(handle))
			return -EBUSY;
		uvd_v5_0_enable_clock_gating(adev, true);

		/* enable HW gates because UVD is idle */
/*		uvd_v5_0_set_hw_clock_gating(adev); */
	} else {
		uvd_v5_0_enable_clock_gating(adev, false);
	}

	uvd_v5_0_set_sw_clock_gating(adev);
	return 0;
}