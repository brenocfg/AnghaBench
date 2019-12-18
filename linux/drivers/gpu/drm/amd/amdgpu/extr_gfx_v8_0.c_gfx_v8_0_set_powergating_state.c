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
struct amdgpu_device {int pg_flags; int asic_type; } ;
typedef  enum amd_powergating_state { ____Placeholder_amd_powergating_state } amd_powergating_state ;

/* Variables and functions */
 int AMD_PG_STATE_GATE ; 
 int AMD_PG_SUPPORT_CP ; 
 int AMD_PG_SUPPORT_GFX_DMG ; 
 int AMD_PG_SUPPORT_GFX_QUICK_MG ; 
 int AMD_PG_SUPPORT_GFX_SMG ; 
 int AMD_PG_SUPPORT_RLC_SMU_HS ; 
#define  CHIP_CARRIZO 132 
#define  CHIP_POLARIS11 131 
#define  CHIP_POLARIS12 130 
#define  CHIP_STONEY 129 
#define  CHIP_VEGAM 128 
 int /*<<< orphan*/  amdgpu_gfx_rlc_enter_safe_mode (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_gfx_rlc_exit_safe_mode (struct amdgpu_device*) ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  cz_enable_cp_power_gating (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  cz_enable_sck_slow_down_on_power_down (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  cz_enable_sck_slow_down_on_power_up (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  cz_update_gfx_cg_power_gating (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  gfx_v8_0_enable_gfx_dynamic_mg_power_gating (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  gfx_v8_0_enable_gfx_static_mg_power_gating (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  polaris11_enable_gfx_quick_mg_power_gating (struct amdgpu_device*,int) ; 

__attribute__((used)) static int gfx_v8_0_set_powergating_state(void *handle,
					  enum amd_powergating_state state)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	bool enable = (state == AMD_PG_STATE_GATE);

	if (amdgpu_sriov_vf(adev))
		return 0;

	if (adev->pg_flags & (AMD_PG_SUPPORT_GFX_SMG |
				AMD_PG_SUPPORT_RLC_SMU_HS |
				AMD_PG_SUPPORT_CP |
				AMD_PG_SUPPORT_GFX_DMG))
		amdgpu_gfx_rlc_enter_safe_mode(adev);
	switch (adev->asic_type) {
	case CHIP_CARRIZO:
	case CHIP_STONEY:

		if (adev->pg_flags & AMD_PG_SUPPORT_RLC_SMU_HS) {
			cz_enable_sck_slow_down_on_power_up(adev, true);
			cz_enable_sck_slow_down_on_power_down(adev, true);
		} else {
			cz_enable_sck_slow_down_on_power_up(adev, false);
			cz_enable_sck_slow_down_on_power_down(adev, false);
		}
		if (adev->pg_flags & AMD_PG_SUPPORT_CP)
			cz_enable_cp_power_gating(adev, true);
		else
			cz_enable_cp_power_gating(adev, false);

		cz_update_gfx_cg_power_gating(adev, enable);

		if ((adev->pg_flags & AMD_PG_SUPPORT_GFX_SMG) && enable)
			gfx_v8_0_enable_gfx_static_mg_power_gating(adev, true);
		else
			gfx_v8_0_enable_gfx_static_mg_power_gating(adev, false);

		if ((adev->pg_flags & AMD_PG_SUPPORT_GFX_DMG) && enable)
			gfx_v8_0_enable_gfx_dynamic_mg_power_gating(adev, true);
		else
			gfx_v8_0_enable_gfx_dynamic_mg_power_gating(adev, false);
		break;
	case CHIP_POLARIS11:
	case CHIP_POLARIS12:
	case CHIP_VEGAM:
		if ((adev->pg_flags & AMD_PG_SUPPORT_GFX_SMG) && enable)
			gfx_v8_0_enable_gfx_static_mg_power_gating(adev, true);
		else
			gfx_v8_0_enable_gfx_static_mg_power_gating(adev, false);

		if ((adev->pg_flags & AMD_PG_SUPPORT_GFX_DMG) && enable)
			gfx_v8_0_enable_gfx_dynamic_mg_power_gating(adev, true);
		else
			gfx_v8_0_enable_gfx_dynamic_mg_power_gating(adev, false);

		if ((adev->pg_flags & AMD_PG_SUPPORT_GFX_QUICK_MG) && enable)
			polaris11_enable_gfx_quick_mg_power_gating(adev, true);
		else
			polaris11_enable_gfx_quick_mg_power_gating(adev, false);
		break;
	default:
		break;
	}
	if (adev->pg_flags & (AMD_PG_SUPPORT_GFX_SMG |
				AMD_PG_SUPPORT_RLC_SMU_HS |
				AMD_PG_SUPPORT_CP |
				AMD_PG_SUPPORT_GFX_DMG))
		amdgpu_gfx_rlc_exit_safe_mode(adev);
	return 0;
}