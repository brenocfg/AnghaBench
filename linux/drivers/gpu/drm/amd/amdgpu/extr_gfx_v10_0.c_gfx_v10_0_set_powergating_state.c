#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  gfx_off_delay_work; } ;
struct amdgpu_device {int asic_type; TYPE_1__ gfx; } ;
typedef  enum amd_powergating_state { ____Placeholder_amd_powergating_state } amd_powergating_state ;

/* Variables and functions */
 int AMD_PG_STATE_GATE ; 
#define  CHIP_NAVI10 129 
#define  CHIP_NAVI14 128 
 int /*<<< orphan*/  amdgpu_gfx_off_ctrl (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gfx_v10_0_set_powergating_state(void *handle,
					  enum amd_powergating_state state)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	bool enable = (state == AMD_PG_STATE_GATE) ? true : false;
	switch (adev->asic_type) {
	case CHIP_NAVI10:
	case CHIP_NAVI14:
		if (!enable) {
			amdgpu_gfx_off_ctrl(adev, false);
			cancel_delayed_work_sync(&adev->gfx.gfx_off_delay_work);
		} else
			amdgpu_gfx_off_ctrl(adev, true);
		break;
	default:
		break;
	}
	return 0;
}