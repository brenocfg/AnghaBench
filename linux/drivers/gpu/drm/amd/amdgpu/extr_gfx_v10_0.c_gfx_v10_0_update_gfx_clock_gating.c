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
struct amdgpu_device {int cg_flags; } ;

/* Variables and functions */
 int AMD_CG_SUPPORT_GFX_3D_CGCG ; 
 int AMD_CG_SUPPORT_GFX_3D_CGLS ; 
 int AMD_CG_SUPPORT_GFX_CGCG ; 
 int AMD_CG_SUPPORT_GFX_CGLS ; 
 int AMD_CG_SUPPORT_GFX_MGCG ; 
 int /*<<< orphan*/  amdgpu_gfx_rlc_enter_safe_mode (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_gfx_rlc_exit_safe_mode (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v10_0_enable_gui_idle_interrupt (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  gfx_v10_0_update_3d_clock_gating (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  gfx_v10_0_update_coarse_grain_clock_gating (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  gfx_v10_0_update_medium_grain_clock_gating (struct amdgpu_device*,int) ; 

__attribute__((used)) static int gfx_v10_0_update_gfx_clock_gating(struct amdgpu_device *adev,
					    bool enable)
{
	amdgpu_gfx_rlc_enter_safe_mode(adev);

	if (enable) {
		/* CGCG/CGLS should be enabled after MGCG/MGLS
		 * ===  MGCG + MGLS ===
		 */
		gfx_v10_0_update_medium_grain_clock_gating(adev, enable);
		/* ===  CGCG /CGLS for GFX 3D Only === */
		gfx_v10_0_update_3d_clock_gating(adev, enable);
		/* ===  CGCG + CGLS === */
		gfx_v10_0_update_coarse_grain_clock_gating(adev, enable);
	} else {
		/* CGCG/CGLS should be disabled before MGCG/MGLS
		 * ===  CGCG + CGLS ===
		 */
		gfx_v10_0_update_coarse_grain_clock_gating(adev, enable);
		/* ===  CGCG /CGLS for GFX 3D Only === */
		gfx_v10_0_update_3d_clock_gating(adev, enable);
		/* ===  MGCG + MGLS === */
		gfx_v10_0_update_medium_grain_clock_gating(adev, enable);
	}

	if (adev->cg_flags &
	    (AMD_CG_SUPPORT_GFX_MGCG |
	     AMD_CG_SUPPORT_GFX_CGLS |
	     AMD_CG_SUPPORT_GFX_CGCG |
	     AMD_CG_SUPPORT_GFX_CGLS |
	     AMD_CG_SUPPORT_GFX_3D_CGCG |
	     AMD_CG_SUPPORT_GFX_3D_CGLS))
		gfx_v10_0_enable_gui_idle_interrupt(adev, enable);

	amdgpu_gfx_rlc_exit_safe_mode(adev);

	return 0;
}