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
typedef  int u32 ;
struct amdgpu_device {int cg_flags; } ;

/* Variables and functions */
 int AMD_CG_SUPPORT_GFX_CP_LS ; 
 int AMD_CG_SUPPORT_GFX_MGCG ; 
 int CGTS_SM_CTRL_REG__LS_OVERRIDE_MASK ; 
 int CGTS_SM_CTRL_REG__OVERRIDE_MASK ; 
 int CP_MEM_SLP_CNTL__CP_MEM_LS_EN_MASK ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int gfx_v6_0_halt_rlc (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v6_0_update_rlc (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  mmCGTS_SM_CTRL_REG ; 
 int /*<<< orphan*/  mmCP_MEM_SLP_CNTL ; 
 int /*<<< orphan*/  mmRLC_CGTT_MGCG_OVERRIDE ; 
 int /*<<< orphan*/  mmRLC_SERDES_WR_CTRL ; 
 int /*<<< orphan*/  mmRLC_SERDES_WR_MASTER_MASK_0 ; 
 int /*<<< orphan*/  mmRLC_SERDES_WR_MASTER_MASK_1 ; 

__attribute__((used)) static void gfx_v6_0_enable_mgcg(struct amdgpu_device *adev, bool enable)
{

	u32 data, orig, tmp = 0;

	if (enable && (adev->cg_flags & AMD_CG_SUPPORT_GFX_MGCG)) {
		orig = data = RREG32(mmCGTS_SM_CTRL_REG);
		data = 0x96940200;
		if (orig != data)
			WREG32(mmCGTS_SM_CTRL_REG, data);

		if (adev->cg_flags & AMD_CG_SUPPORT_GFX_CP_LS) {
			orig = data = RREG32(mmCP_MEM_SLP_CNTL);
			data |= CP_MEM_SLP_CNTL__CP_MEM_LS_EN_MASK;
			if (orig != data)
				WREG32(mmCP_MEM_SLP_CNTL, data);
		}

		orig = data = RREG32(mmRLC_CGTT_MGCG_OVERRIDE);
		data &= 0xffffffc0;
		if (orig != data)
			WREG32(mmRLC_CGTT_MGCG_OVERRIDE, data);

		tmp = gfx_v6_0_halt_rlc(adev);

		WREG32(mmRLC_SERDES_WR_MASTER_MASK_0, 0xffffffff);
		WREG32(mmRLC_SERDES_WR_MASTER_MASK_1, 0xffffffff);
		WREG32(mmRLC_SERDES_WR_CTRL, 0x00d000ff);

		gfx_v6_0_update_rlc(adev, tmp);
	} else {
		orig = data = RREG32(mmRLC_CGTT_MGCG_OVERRIDE);
		data |= 0x00000003;
		if (orig != data)
			WREG32(mmRLC_CGTT_MGCG_OVERRIDE, data);

		data = RREG32(mmCP_MEM_SLP_CNTL);
		if (data & CP_MEM_SLP_CNTL__CP_MEM_LS_EN_MASK) {
			data &= ~CP_MEM_SLP_CNTL__CP_MEM_LS_EN_MASK;
			WREG32(mmCP_MEM_SLP_CNTL, data);
		}
		orig = data = RREG32(mmCGTS_SM_CTRL_REG);
		data |= CGTS_SM_CTRL_REG__LS_OVERRIDE_MASK | CGTS_SM_CTRL_REG__OVERRIDE_MASK;
		if (orig != data)
			WREG32(mmCGTS_SM_CTRL_REG, data);

		tmp = gfx_v6_0_halt_rlc(adev);

		WREG32(mmRLC_SERDES_WR_MASTER_MASK_0, 0xffffffff);
		WREG32(mmRLC_SERDES_WR_MASTER_MASK_1, 0xffffffff);
		WREG32(mmRLC_SERDES_WR_CTRL, 0x00e000ff);

		gfx_v6_0_update_rlc(adev, tmp);
	}
}