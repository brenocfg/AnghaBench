#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* pp_funcs; } ;
struct amdgpu_device {int asic_type; int pg_flags; TYPE_2__ powerplay; } ;
typedef  enum amd_powergating_state { ____Placeholder_amd_powergating_state } amd_powergating_state ;
struct TYPE_3__ {int /*<<< orphan*/  set_powergating_by_smu; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_IP_BLOCK_TYPE_GFX ; 
 int AMD_PG_STATE_GATE ; 
 int AMD_PG_SUPPORT_CP ; 
 int AMD_PG_SUPPORT_RLC_SMU_HS ; 
#define  CHIP_RAVEN 129 
#define  CHIP_VEGA12 128 
 int /*<<< orphan*/  amdgpu_dpm_set_powergating_by_smu (struct amdgpu_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gfx_v9_0_enable_cp_power_gating (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  gfx_v9_0_enable_sck_slow_down_on_power_down (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  gfx_v9_0_enable_sck_slow_down_on_power_up (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  gfx_v9_0_update_gfx_cg_power_gating (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  gfx_v9_0_update_gfx_mg_power_gating (struct amdgpu_device*,int) ; 

__attribute__((used)) static int gfx_v9_0_set_powergating_state(void *handle,
					  enum amd_powergating_state state)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	bool enable = (state == AMD_PG_STATE_GATE) ? true : false;

	switch (adev->asic_type) {
	case CHIP_RAVEN:
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
		gfx_v9_0_update_gfx_cg_power_gating(adev, enable);

		/* update mgcg state */
		gfx_v9_0_update_gfx_mg_power_gating(adev, enable);

		/* set gfx off through smu */
		if (enable && adev->powerplay.pp_funcs->set_powergating_by_smu)
			amdgpu_dpm_set_powergating_by_smu(adev, AMD_IP_BLOCK_TYPE_GFX, true);
		break;
	case CHIP_VEGA12:
		/* set gfx off through smu */
		if (enable && adev->powerplay.pp_funcs->set_powergating_by_smu)
			amdgpu_dpm_set_powergating_by_smu(adev, AMD_IP_BLOCK_TYPE_GFX, true);
		break;
	default:
		break;
	}

	return 0;
}