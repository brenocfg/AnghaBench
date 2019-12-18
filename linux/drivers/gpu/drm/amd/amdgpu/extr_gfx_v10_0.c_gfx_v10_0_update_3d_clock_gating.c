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
typedef  int uint32_t ;
struct amdgpu_device {int cg_flags; } ;

/* Variables and functions */
 int AMD_CG_SUPPORT_GFX_3D_CGCG ; 
 int AMD_CG_SUPPORT_GFX_3D_CGLS ; 
 int CP_RB_WPTR_POLL_CNTL__IDLE_POLL_COUNT__SHIFT ; 
 int CP_RB_WPTR_POLL_CNTL__POLL_FREQUENCY__SHIFT ; 
 int /*<<< orphan*/  GC ; 
 int RLC_CGCG_CGLS_CTRL_3D__CGCG_EN_MASK ; 
 int RLC_CGCG_CGLS_CTRL_3D__CGCG_GFX_IDLE_THRESHOLD__SHIFT ; 
 int RLC_CGCG_CGLS_CTRL_3D__CGLS_EN_MASK ; 
 int RLC_CGCG_CGLS_CTRL_3D__CGLS_REP_COMPANSAT_DELAY__SHIFT ; 
 int RLC_CGTT_MGCG_OVERRIDE__GFXIP_GFX3D_CG_OVERRIDE_MASK ; 
 int RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmCP_RB_WPTR_POLL_CNTL ; 
 int /*<<< orphan*/  mmRLC_CGCG_CGLS_CTRL_3D ; 
 int /*<<< orphan*/  mmRLC_CGTT_MGCG_OVERRIDE ; 

__attribute__((used)) static void gfx_v10_0_update_3d_clock_gating(struct amdgpu_device *adev,
					   bool enable)
{
	uint32_t data, def;

	/* Enable 3D CGCG/CGLS */
	if (enable && (adev->cg_flags & AMD_CG_SUPPORT_GFX_3D_CGCG)) {
		/* write cmd to clear cgcg/cgls ov */
		def = data = RREG32_SOC15(GC, 0, mmRLC_CGTT_MGCG_OVERRIDE);
		/* unset CGCG override */
		data &= ~RLC_CGTT_MGCG_OVERRIDE__GFXIP_GFX3D_CG_OVERRIDE_MASK;
		/* update CGCG and CGLS override bits */
		if (def != data)
			WREG32_SOC15(GC, 0, mmRLC_CGTT_MGCG_OVERRIDE, data);
		/* enable 3Dcgcg FSM(0x0000363f) */
		def = RREG32_SOC15(GC, 0, mmRLC_CGCG_CGLS_CTRL_3D);
		data = (0x36 << RLC_CGCG_CGLS_CTRL_3D__CGCG_GFX_IDLE_THRESHOLD__SHIFT) |
			RLC_CGCG_CGLS_CTRL_3D__CGCG_EN_MASK;
		if (adev->cg_flags & AMD_CG_SUPPORT_GFX_3D_CGLS)
			data |= (0x000F << RLC_CGCG_CGLS_CTRL_3D__CGLS_REP_COMPANSAT_DELAY__SHIFT) |
				RLC_CGCG_CGLS_CTRL_3D__CGLS_EN_MASK;
		if (def != data)
			WREG32_SOC15(GC, 0, mmRLC_CGCG_CGLS_CTRL_3D, data);

		/* set IDLE_POLL_COUNT(0x00900100) */
		def = RREG32_SOC15(GC, 0, mmCP_RB_WPTR_POLL_CNTL);
		data = (0x0100 << CP_RB_WPTR_POLL_CNTL__POLL_FREQUENCY__SHIFT) |
			(0x0090 << CP_RB_WPTR_POLL_CNTL__IDLE_POLL_COUNT__SHIFT);
		if (def != data)
			WREG32_SOC15(GC, 0, mmCP_RB_WPTR_POLL_CNTL, data);
	} else {
		/* Disable CGCG/CGLS */
		def = data = RREG32_SOC15(GC, 0, mmRLC_CGCG_CGLS_CTRL_3D);
		/* disable cgcg, cgls should be disabled */
		data &= ~(RLC_CGCG_CGLS_CTRL_3D__CGCG_EN_MASK |
			  RLC_CGCG_CGLS_CTRL_3D__CGLS_EN_MASK);
		/* disable cgcg and cgls in FSM */
		if (def != data)
			WREG32_SOC15(GC, 0, mmRLC_CGCG_CGLS_CTRL_3D, data);
	}
}