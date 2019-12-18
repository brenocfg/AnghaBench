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
struct amdgpu_device {int cg_flags; int flags; } ;

/* Variables and functions */
 int AMD_CG_SUPPORT_GFX_CGTS ; 
 int AMD_CG_SUPPORT_GFX_CGTS_LS ; 
 int AMD_CG_SUPPORT_GFX_CP_LS ; 
 int AMD_CG_SUPPORT_GFX_MGCG ; 
 int AMD_CG_SUPPORT_GFX_MGLS ; 
 int AMD_CG_SUPPORT_GFX_RLC_LS ; 
 int AMD_IS_APU ; 
 int /*<<< orphan*/  BPM_REG_MGCG_OVERRIDE ; 
 int CGTS_SM_CTRL_REG__LS_OVERRIDE_MASK ; 
 int CGTS_SM_CTRL_REG__ON_MONITOR_ADD_EN_MASK ; 
 int CGTS_SM_CTRL_REG__ON_MONITOR_ADD__SHIFT ; 
 int CGTS_SM_CTRL_REG__OVERRIDE_MASK ; 
 int CGTS_SM_CTRL_REG__SM_MODE_ENABLE_MASK ; 
 int CGTS_SM_CTRL_REG__SM_MODE_MASK ; 
 int CGTS_SM_CTRL_REG__SM_MODE__SHIFT ; 
 int /*<<< orphan*/  CLE_BPM_SERDES_CMD ; 
 int /*<<< orphan*/  CP_MEM_LS_EN ; 
 int /*<<< orphan*/  CP_MEM_SLP_CNTL ; 
 int CP_MEM_SLP_CNTL__CP_MEM_LS_EN_MASK ; 
 int RLC_CGTT_MGCG_OVERRIDE__CPF_MASK ; 
 int RLC_CGTT_MGCG_OVERRIDE__GRBM_MASK ; 
 int RLC_CGTT_MGCG_OVERRIDE__MGCG_MASK ; 
 int RLC_CGTT_MGCG_OVERRIDE__RLC_MASK ; 
 int /*<<< orphan*/  RLC_MEM_LS_EN ; 
 int /*<<< orphan*/  RLC_MEM_SLP_CNTL ; 
 int RLC_MEM_SLP_CNTL__RLC_MEM_LS_EN_MASK ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_BPM_SERDES_CMD ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  amdgpu_gfx_rlc_enter_safe_mode (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_gfx_rlc_exit_safe_mode (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v8_0_send_serdes_cmd (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfx_v8_0_wait_for_rlc_serdes (struct amdgpu_device*) ; 
 int /*<<< orphan*/  mmCGTS_SM_CTRL_REG ; 
 int /*<<< orphan*/  mmCP_MEM_SLP_CNTL ; 
 int /*<<< orphan*/  mmRLC_CGTT_MGCG_OVERRIDE ; 
 int /*<<< orphan*/  mmRLC_MEM_SLP_CNTL ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void gfx_v8_0_update_medium_grain_clock_gating(struct amdgpu_device *adev,
						      bool enable)
{
	uint32_t temp, data;

	amdgpu_gfx_rlc_enter_safe_mode(adev);

	/* It is disabled by HW by default */
	if (enable && (adev->cg_flags & AMD_CG_SUPPORT_GFX_MGCG)) {
		if (adev->cg_flags & AMD_CG_SUPPORT_GFX_MGLS) {
			if (adev->cg_flags & AMD_CG_SUPPORT_GFX_RLC_LS)
				/* 1 - RLC memory Light sleep */
				WREG32_FIELD(RLC_MEM_SLP_CNTL, RLC_MEM_LS_EN, 1);

			if (adev->cg_flags & AMD_CG_SUPPORT_GFX_CP_LS)
				WREG32_FIELD(CP_MEM_SLP_CNTL, CP_MEM_LS_EN, 1);
		}

		/* 3 - RLC_CGTT_MGCG_OVERRIDE */
		temp = data = RREG32(mmRLC_CGTT_MGCG_OVERRIDE);
		if (adev->flags & AMD_IS_APU)
			data &= ~(RLC_CGTT_MGCG_OVERRIDE__CPF_MASK |
				  RLC_CGTT_MGCG_OVERRIDE__RLC_MASK |
				  RLC_CGTT_MGCG_OVERRIDE__MGCG_MASK);
		else
			data &= ~(RLC_CGTT_MGCG_OVERRIDE__CPF_MASK |
				  RLC_CGTT_MGCG_OVERRIDE__RLC_MASK |
				  RLC_CGTT_MGCG_OVERRIDE__MGCG_MASK |
				  RLC_CGTT_MGCG_OVERRIDE__GRBM_MASK);

		if (temp != data)
			WREG32(mmRLC_CGTT_MGCG_OVERRIDE, data);

		/* 4 - wait for RLC_SERDES_CU_MASTER & RLC_SERDES_NONCU_MASTER idle */
		gfx_v8_0_wait_for_rlc_serdes(adev);

		/* 5 - clear mgcg override */
		gfx_v8_0_send_serdes_cmd(adev, BPM_REG_MGCG_OVERRIDE, CLE_BPM_SERDES_CMD);

		if (adev->cg_flags & AMD_CG_SUPPORT_GFX_CGTS) {
			/* 6 - Enable CGTS(Tree Shade) MGCG /MGLS */
			temp = data = RREG32(mmCGTS_SM_CTRL_REG);
			data &= ~(CGTS_SM_CTRL_REG__SM_MODE_MASK);
			data |= (0x2 << CGTS_SM_CTRL_REG__SM_MODE__SHIFT);
			data |= CGTS_SM_CTRL_REG__SM_MODE_ENABLE_MASK;
			data &= ~CGTS_SM_CTRL_REG__OVERRIDE_MASK;
			if ((adev->cg_flags & AMD_CG_SUPPORT_GFX_MGLS) &&
			    (adev->cg_flags & AMD_CG_SUPPORT_GFX_CGTS_LS))
				data &= ~CGTS_SM_CTRL_REG__LS_OVERRIDE_MASK;
			data |= CGTS_SM_CTRL_REG__ON_MONITOR_ADD_EN_MASK;
			data |= (0x96 << CGTS_SM_CTRL_REG__ON_MONITOR_ADD__SHIFT);
			if (temp != data)
				WREG32(mmCGTS_SM_CTRL_REG, data);
		}
		udelay(50);

		/* 7 - wait for RLC_SERDES_CU_MASTER & RLC_SERDES_NONCU_MASTER idle */
		gfx_v8_0_wait_for_rlc_serdes(adev);
	} else {
		/* 1 - MGCG_OVERRIDE[0] for CP and MGCG_OVERRIDE[1] for RLC */
		temp = data = RREG32(mmRLC_CGTT_MGCG_OVERRIDE);
		data |= (RLC_CGTT_MGCG_OVERRIDE__CPF_MASK |
				RLC_CGTT_MGCG_OVERRIDE__RLC_MASK |
				RLC_CGTT_MGCG_OVERRIDE__MGCG_MASK |
				RLC_CGTT_MGCG_OVERRIDE__GRBM_MASK);
		if (temp != data)
			WREG32(mmRLC_CGTT_MGCG_OVERRIDE, data);

		/* 2 - disable MGLS in RLC */
		data = RREG32(mmRLC_MEM_SLP_CNTL);
		if (data & RLC_MEM_SLP_CNTL__RLC_MEM_LS_EN_MASK) {
			data &= ~RLC_MEM_SLP_CNTL__RLC_MEM_LS_EN_MASK;
			WREG32(mmRLC_MEM_SLP_CNTL, data);
		}

		/* 3 - disable MGLS in CP */
		data = RREG32(mmCP_MEM_SLP_CNTL);
		if (data & CP_MEM_SLP_CNTL__CP_MEM_LS_EN_MASK) {
			data &= ~CP_MEM_SLP_CNTL__CP_MEM_LS_EN_MASK;
			WREG32(mmCP_MEM_SLP_CNTL, data);
		}

		/* 4 - Disable CGTS(Tree Shade) MGCG and MGLS */
		temp = data = RREG32(mmCGTS_SM_CTRL_REG);
		data |= (CGTS_SM_CTRL_REG__OVERRIDE_MASK |
				CGTS_SM_CTRL_REG__LS_OVERRIDE_MASK);
		if (temp != data)
			WREG32(mmCGTS_SM_CTRL_REG, data);

		/* 5 - wait for RLC_SERDES_CU_MASTER & RLC_SERDES_NONCU_MASTER idle */
		gfx_v8_0_wait_for_rlc_serdes(adev);

		/* 6 - set mgcg override */
		gfx_v8_0_send_serdes_cmd(adev, BPM_REG_MGCG_OVERRIDE, SET_BPM_SERDES_CMD);

		udelay(50);

		/* 7- wait for RLC_SERDES_CU_MASTER & RLC_SERDES_NONCU_MASTER idle */
		gfx_v8_0_wait_for_rlc_serdes(adev);
	}

	amdgpu_gfx_rlc_exit_safe_mode(adev);
}