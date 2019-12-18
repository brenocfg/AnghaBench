#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int in_safe_mode; TYPE_1__* funcs; } ;
struct TYPE_6__ {TYPE_2__ rlc; } ;
struct amdgpu_device {int cg_flags; TYPE_3__ gfx; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* set_safe_mode ) (struct amdgpu_device*) ;int /*<<< orphan*/  (* is_rlc_enabled ) (struct amdgpu_device*) ;} ;

/* Variables and functions */
 int AMD_CG_SUPPORT_GFX_3D_CGCG ; 
 int AMD_CG_SUPPORT_GFX_CGCG ; 
 int AMD_CG_SUPPORT_GFX_MGCG ; 
 int /*<<< orphan*/  stub1 (struct amdgpu_device*) ; 
 int /*<<< orphan*/  stub2 (struct amdgpu_device*) ; 

void amdgpu_gfx_rlc_enter_safe_mode(struct amdgpu_device *adev)
{
	if (adev->gfx.rlc.in_safe_mode)
		return;

	/* if RLC is not enabled, do nothing */
	if (!adev->gfx.rlc.funcs->is_rlc_enabled(adev))
		return;

	if (adev->cg_flags &
	    (AMD_CG_SUPPORT_GFX_CGCG | AMD_CG_SUPPORT_GFX_MGCG |
	     AMD_CG_SUPPORT_GFX_3D_CGCG)) {
		adev->gfx.rlc.funcs->set_safe_mode(adev);
		adev->gfx.rlc.in_safe_mode = true;
	}
}