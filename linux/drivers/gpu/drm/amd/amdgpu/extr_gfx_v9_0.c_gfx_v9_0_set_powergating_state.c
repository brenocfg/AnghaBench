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
struct amdgpu_device {int asic_type; int pg_flags; TYPE_1__ gfx; int /*<<< orphan*/  smu; } ;
typedef  enum amd_powergating_state { ____Placeholder_amd_powergating_state } amd_powergating_state ;

/* Variables and functions */
 int AMD_PG_STATE_GATE ; 
 int AMD_PG_SUPPORT_CP ; 
 int AMD_PG_SUPPORT_RLC_SMU_HS ; 
#define  CHIP_RAVEN 130 
#define  CHIP_RENOIR 129 
#define  CHIP_VEGA12 128 
 int /*<<< orphan*/  amdgpu_gfx_off_ctrl (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfx_v9_0_enable_cp_power_gating (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  gfx_v9_0_enable_sck_slow_down_on_power_down (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  gfx_v9_0_enable_sck_slow_down_on_power_up (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  gfx_v9_0_update_gfx_cg_power_gating (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  gfx_v9_0_update_gfx_mg_power_gating (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  is_support_sw_smu (struct amdgpu_device*) ; 
 int /*<<< orphan*/  smu_set_gfx_cgpg (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int gfx_v9_0_set_powergating_state(void *handle,
					  enum amd_powergating_state state)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	bool enable = (state == AMD_PG_STATE_GATE) ? true : false;

	switch (adev->asic_type) {
	case CHIP_RAVEN:
	case CHIP_RENOIR:
		if (!enable) {
			amdgpu_gfx_off_ctrl(adev, false);
			cancel_delayed_work_sync(&adev->gfx.gfx_off_delay_work);
		}
		if (adev->pg_flags & AMD_PG_SUPPORT_RLC_SMU_HS) {
			gfx_v9_0_enable_sck_slow_down_on_power_up(adev, true);
			gfx_v9_0_enable_sck_slow_down_on_power_down(adev, true);
		} else {
			gfx_v9_0_enable_sck_slow_down_on_power_up(adev, false);
			gfx_v9_0_enable_sck_slow_down_on_power_down(adev, false);
		}

		if (adev->pg_flags & AMD_PG_SUPPORT_CP)
			gfx_v9_0_enable_cp_power_gating(adev, true);
		else
			gfx_v9_0_enable_cp_power_gating(adev, false);

		/* update gfx cgpg state */
		if (is_support_sw_smu(adev) && enable)
			smu_set_gfx_cgpg(&adev->smu, enable);
		gfx_v9_0_update_gfx_cg_power_gating(adev, enable);

		/* update mgcg state */
		gfx_v9_0_update_gfx_mg_power_gating(adev, enable);

		if (enable)
			amdgpu_gfx_off_ctrl(adev, true);
		break;
	case CHIP_VEGA12:
		if (!enable) {
			amdgpu_gfx_off_ctrl(adev, false);
			cancel_delayed_work_sync(&adev->gfx.gfx_off_delay_work);
		} else {
			amdgpu_gfx_off_ctrl(adev, true);
		}
		break;
	default:
		break;
	}

	return 0;
}