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
 int AMD_CG_SUPPORT_GFX_CP_LS ; 
 int AMD_CG_SUPPORT_GFX_MGCG ; 
 int AMD_CG_SUPPORT_GFX_MGLS ; 
 int AMD_CG_SUPPORT_GFX_RLC_LS ; 
 int CP_MEM_SLP_CNTL__CP_MEM_LS_EN_MASK ; 
 int /*<<< orphan*/  GC ; 
 int RLC_CGTT_MGCG_OVERRIDE__GFXIP_MGCG_OVERRIDE_MASK ; 
 int RLC_CGTT_MGCG_OVERRIDE__GFXIP_MGLS_OVERRIDE_MASK ; 
 int RLC_CGTT_MGCG_OVERRIDE__GRBM_CGTT_SCLK_OVERRIDE_MASK ; 
 int RLC_CGTT_MGCG_OVERRIDE__RLC_CGTT_SCLK_OVERRIDE_MASK ; 
 int RLC_MEM_SLP_CNTL__RLC_MEM_LS_EN_MASK ; 
 int RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmCP_MEM_SLP_CNTL ; 
 int /*<<< orphan*/  mmRLC_CGTT_MGCG_OVERRIDE ; 
 int /*<<< orphan*/  mmRLC_MEM_SLP_CNTL ; 

__attribute__((used)) static void gfx_v10_0_update_medium_grain_clock_gating(struct amdgpu_device *adev,
						      bool enable)
{
	uint32_t data, def;

	/* It is disabled by HW by default */
	if (enable && (adev->cg_flags & AMD_CG_SUPPORT_GFX_MGCG)) {
		/* 1 - RLC_CGTT_MGCG_OVERRIDE */
		def = data = RREG32_SOC15(GC, 0, mmRLC_CGTT_MGCG_OVERRIDE);
		data &= ~(RLC_CGTT_MGCG_OVERRIDE__GRBM_CGTT_SCLK_OVERRIDE_MASK |
			  RLC_CGTT_MGCG_OVERRIDE__GFXIP_MGCG_OVERRIDE_MASK |
			  RLC_CGTT_MGCG_OVERRIDE__GFXIP_MGLS_OVERRIDE_MASK);

		/* only for Vega10 & Raven1 */
		data |= RLC_CGTT_MGCG_OVERRIDE__RLC_CGTT_SCLK_OVERRIDE_MASK;

		if (def != data)
			WREG32_SOC15(GC, 0, mmRLC_CGTT_MGCG_OVERRIDE, data);

		/* MGLS is a global flag to control all MGLS in GFX */
		if (adev->cg_flags & AMD_CG_SUPPORT_GFX_MGLS) {
			/* 2 - RLC memory Light sleep */
			if (adev->cg_flags & AMD_CG_SUPPORT_GFX_RLC_LS) {
				def = data = RREG32_SOC15(GC, 0, mmRLC_MEM_SLP_CNTL);
				data |= RLC_MEM_SLP_CNTL__RLC_MEM_LS_EN_MASK;
				if (def != data)
					WREG32_SOC15(GC, 0, mmRLC_MEM_SLP_CNTL, data);
			}
			/* 3 - CP memory Light sleep */
			if (adev->cg_flags & AMD_CG_SUPPORT_GFX_CP_LS) {
				def = data = RREG32_SOC15(GC, 0, mmCP_MEM_SLP_CNTL);
				data |= CP_MEM_SLP_CNTL__CP_MEM_LS_EN_MASK;
				if (def != data)
					WREG32_SOC15(GC, 0, mmCP_MEM_SLP_CNTL, data);
			}
		}
	} else {
		/* 1 - MGCG_OVERRIDE */
		def = data = RREG32_SOC15(GC, 0, mmRLC_CGTT_MGCG_OVERRIDE);
		data |= (RLC_CGTT_MGCG_OVERRIDE__RLC_CGTT_SCLK_OVERRIDE_MASK |
			 RLC_CGTT_MGCG_OVERRIDE__GRBM_CGTT_SCLK_OVERRIDE_MASK |
			 RLC_CGTT_MGCG_OVERRIDE__GFXIP_MGCG_OVERRIDE_MASK |
			 RLC_CGTT_MGCG_OVERRIDE__GFXIP_MGLS_OVERRIDE_MASK);
		if (def != data)
			WREG32_SOC15(GC, 0, mmRLC_CGTT_MGCG_OVERRIDE, data);

		/* 2 - disable MGLS in RLC */
		data = RREG32_SOC15(GC, 0, mmRLC_MEM_SLP_CNTL);
		if (data & RLC_MEM_SLP_CNTL__RLC_MEM_LS_EN_MASK) {
			data &= ~RLC_MEM_SLP_CNTL__RLC_MEM_LS_EN_MASK;
			WREG32_SOC15(GC, 0, mmRLC_MEM_SLP_CNTL, data);
		}

		/* 3 - disable MGLS in CP */
		data = RREG32_SOC15(GC, 0, mmCP_MEM_SLP_CNTL);
		if (data & CP_MEM_SLP_CNTL__CP_MEM_LS_EN_MASK) {
			data &= ~CP_MEM_SLP_CNTL__CP_MEM_LS_EN_MASK;
			WREG32_SOC15(GC, 0, mmCP_MEM_SLP_CNTL, data);
		}
	}
}