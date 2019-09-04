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
typedef  int uint32_t ;
struct TYPE_3__ {int in_safe_mode; } ;
struct TYPE_4__ {TYPE_1__ rlc; } ;
struct amdgpu_device {int cg_flags; TYPE_2__ gfx; } ;

/* Variables and functions */
 int AMD_CG_SUPPORT_GFX_CGCG ; 
 int AMD_CG_SUPPORT_GFX_MGCG ; 
 int /*<<< orphan*/  GC ; 
 int RLC_CNTL__RLC_ENABLE_F32_MASK ; 
 int RLC_SAFE_MODE__CMD_MASK ; 
 int RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmRLC_CNTL ; 
 int /*<<< orphan*/  mmRLC_SAFE_MODE ; 

__attribute__((used)) static void gfx_v9_0_exit_rlc_safe_mode(struct amdgpu_device *adev)
{
	uint32_t rlc_setting, data;

	if (!adev->gfx.rlc.in_safe_mode)
		return;

	/* if RLC is not enabled, do nothing */
	rlc_setting = RREG32_SOC15(GC, 0, mmRLC_CNTL);
	if (!(rlc_setting & RLC_CNTL__RLC_ENABLE_F32_MASK))
		return;

	if (adev->cg_flags &
	    (AMD_CG_SUPPORT_GFX_CGCG | AMD_CG_SUPPORT_GFX_MGCG)) {
		/*
		 * Try to exit safe mode only if it is already in safe
		 * mode.
		 */
		data = RLC_SAFE_MODE__CMD_MASK;
		WREG32_SOC15(GC, 0, mmRLC_SAFE_MODE, data);
		adev->gfx.rlc.in_safe_mode = false;
	}
}