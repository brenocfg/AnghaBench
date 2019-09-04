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
typedef  int uint32_t ;
struct TYPE_5__ {TYPE_1__* funcs; } ;
struct TYPE_6__ {TYPE_2__ rlc; } ;
struct amdgpu_device {int cg_flags; TYPE_3__ gfx; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* exit_safe_mode ) (struct amdgpu_device*) ;int /*<<< orphan*/  (* enter_safe_mode ) (struct amdgpu_device*) ;} ;

/* Variables and functions */
 int AMD_CG_SUPPORT_GFX_CGCG ; 
 int AMD_CG_SUPPORT_GFX_CGLS ; 
 int CP_RB_WPTR_POLL_CNTL__IDLE_POLL_COUNT__SHIFT ; 
 int CP_RB_WPTR_POLL_CNTL__POLL_FREQUENCY__SHIFT ; 
 int /*<<< orphan*/  GC ; 
 int RLC_CGCG_CGLS_CTRL__CGCG_EN_MASK ; 
 int RLC_CGCG_CGLS_CTRL__CGCG_GFX_IDLE_THRESHOLD__SHIFT ; 
 int RLC_CGCG_CGLS_CTRL__CGLS_EN_MASK ; 
 int RLC_CGCG_CGLS_CTRL__CGLS_REP_COMPANSAT_DELAY__SHIFT ; 
 int RLC_CGTT_MGCG_OVERRIDE__GFXIP_CGCG_OVERRIDE_MASK ; 
 int RLC_CGTT_MGCG_OVERRIDE__GFXIP_CGLS_OVERRIDE_MASK ; 
 int RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmCP_RB_WPTR_POLL_CNTL ; 
 int /*<<< orphan*/  mmRLC_CGCG_CGLS_CTRL ; 
 int /*<<< orphan*/  mmRLC_CGTT_MGCG_OVERRIDE ; 
 int /*<<< orphan*/  stub1 (struct amdgpu_device*) ; 
 int /*<<< orphan*/  stub2 (struct amdgpu_device*) ; 

__attribute__((used)) static void gfx_v9_0_update_coarse_grain_clock_gating(struct amdgpu_device *adev,
						      bool enable)
{
	uint32_t def, data;

	adev->gfx.rlc.funcs->enter_safe_mode(adev);

	if (enable && (adev->cg_flags & AMD_CG_SUPPORT_GFX_CGCG)) {
		def = data = RREG32_SOC15(GC, 0, mmRLC_CGTT_MGCG_OVERRIDE);
		/* unset CGCG override */
		data &= ~RLC_CGTT_MGCG_OVERRIDE__GFXIP_CGCG_OVERRIDE_MASK;
		if (adev->cg_flags & AMD_CG_SUPPORT_GFX_CGLS)
			data &= ~RLC_CGTT_MGCG_OVERRIDE__GFXIP_CGLS_OVERRIDE_MASK;
		else
			data |= RLC_CGTT_MGCG_OVERRIDE__GFXIP_CGLS_OVERRIDE_MASK;
		/* update CGCG and CGLS override bits */
		if (def != data)
			WREG32_SOC15(GC, 0, mmRLC_CGTT_MGCG_OVERRIDE, data);

		/* enable cgcg FSM(0x0000363F) */
		def = RREG32_SOC15(GC, 0, mmRLC_CGCG_CGLS_CTRL);

		data = (0x36 << RLC_CGCG_CGLS_CTRL__CGCG_GFX_IDLE_THRESHOLD__SHIFT) |
			RLC_CGCG_CGLS_CTRL__CGCG_EN_MASK;
		if (adev->cg_flags & AMD_CG_SUPPORT_GFX_CGLS)
			data |= (0x000F << RLC_CGCG_CGLS_CTRL__CGLS_REP_COMPANSAT_DELAY__SHIFT) |
				RLC_CGCG_CGLS_CTRL__CGLS_EN_MASK;
		if (def != data)
			WREG32_SOC15(GC, 0, mmRLC_CGCG_CGLS_CTRL, data);

		/* set IDLE_POLL_COUNT(0x00900100) */
		def = RREG32_SOC15(GC, 0, mmCP_RB_WPTR_POLL_CNTL);
		data = (0x0100 << CP_RB_WPTR_POLL_CNTL__POLL_FREQUENCY__SHIFT) |
			(0x0090 << CP_RB_WPTR_POLL_CNTL__IDLE_POLL_COUNT__SHIFT);
		if (def != data)
			WREG32_SOC15(GC, 0, mmCP_RB_WPTR_POLL_CNTL, data);
	} else {
		def = data = RREG32_SOC15(GC, 0, mmRLC_CGCG_CGLS_CTRL);
		/* reset CGCG/CGLS bits */
		data &= ~(RLC_CGCG_CGLS_CTRL__CGCG_EN_MASK | RLC_CGCG_CGLS_CTRL__CGLS_EN_MASK);
		/* disable cgcg and cgls in FSM */
		if (def != data)
			WREG32_SOC15(GC, 0, mmRLC_CGCG_CGLS_CTRL, data);
	}

	adev->gfx.rlc.funcs->exit_safe_mode(adev);
}