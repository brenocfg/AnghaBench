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
typedef  enum amd_powergating_state { ____Placeholder_amd_powergating_state } amd_powergating_state ;

/* Variables and functions */
 int AMD_PG_STATE_GATE ; 
#define  CHIP_RAVEN 128 
 int /*<<< orphan*/  sdma_v4_1_update_power_gating (struct amdgpu_device*,int) ; 

__attribute__((used)) static int sdma_v4_0_set_powergating_state(void *handle,
					  enum amd_powergating_state state)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	switch (adev->asic_type) {
	case CHIP_RAVEN:
		sdma_v4_1_update_power_gating(adev,
				state == AMD_PG_STATE_GATE ? true : false);
		break;
	default:
		break;
	}

	return 0;
}