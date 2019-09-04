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
struct rv7xx_power_info {scalar_t__ mgcgtssm; } ;
struct radeon_device {scalar_t__ family; } ;
struct evergreen_power_info {scalar_t__ mcls; } ;

/* Variables and functions */
 int CEDAR_MGCGCGTSSMCTRL_DFLT ; 
 int /*<<< orphan*/  CGTS_SM_CTRL_REG ; 
 int /*<<< orphan*/  CG_CGTT_LOCAL_0 ; 
 int /*<<< orphan*/  CG_CGTT_LOCAL_1 ; 
 int /*<<< orphan*/  CG_CGTT_LOCAL_2 ; 
 int /*<<< orphan*/  CG_CGTT_LOCAL_3 ; 
 scalar_t__ CHIP_CEDAR ; 
 scalar_t__ CHIP_REDWOOD ; 
 int CYPRESS_MGCGCGTSSMCTRL_DFLT ; 
 int CYPRESS_MGCGTTLOCAL0_DFLT ; 
 int CYPRESS_MGCGTTLOCAL1_DFLT ; 
 int CYPRESS_MGCGTTLOCAL2_DFLT ; 
 int CYPRESS_MGCGTTLOCAL3_DFLT ; 
 int /*<<< orphan*/  GRBM_GFX_INDEX ; 
 int /*<<< orphan*/  MC_CITF_MISC_RD_CG ; 
 int /*<<< orphan*/  MC_CITF_MISC_VM_CG ; 
 int /*<<< orphan*/  MC_CITF_MISC_WR_CG ; 
 int /*<<< orphan*/  MC_HUB_MISC_HUB_CG ; 
 int /*<<< orphan*/  MC_HUB_MISC_SIP_CG ; 
 int /*<<< orphan*/  MC_HUB_MISC_VM_CG ; 
 int /*<<< orphan*/  MC_XPB_CLK_GAT ; 
 int /*<<< orphan*/  MEM_LS_ENABLE ; 
 int REDWOOD_MGCGCGTSSMCTRL_DFLT ; 
 int /*<<< orphan*/  VM_L2_CG ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_CG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct evergreen_power_info* evergreen_get_pi (struct radeon_device*) ; 
 struct rv7xx_power_info* rv770_get_pi (struct radeon_device*) ; 

__attribute__((used)) static void cypress_mg_clock_gating_enable(struct radeon_device *rdev,
					   bool enable)
{
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);
	struct evergreen_power_info *eg_pi = evergreen_get_pi(rdev);

	if (enable) {
		u32 cgts_sm_ctrl_reg;

		if (rdev->family == CHIP_CEDAR)
			cgts_sm_ctrl_reg = CEDAR_MGCGCGTSSMCTRL_DFLT;
		else if (rdev->family == CHIP_REDWOOD)
			cgts_sm_ctrl_reg = REDWOOD_MGCGCGTSSMCTRL_DFLT;
		else
			cgts_sm_ctrl_reg = CYPRESS_MGCGCGTSSMCTRL_DFLT;

		WREG32(GRBM_GFX_INDEX, 0xC0000000);

		WREG32_CG(CG_CGTT_LOCAL_0, CYPRESS_MGCGTTLOCAL0_DFLT);
		WREG32_CG(CG_CGTT_LOCAL_1, CYPRESS_MGCGTTLOCAL1_DFLT & 0xFFFFCFFF);
		WREG32_CG(CG_CGTT_LOCAL_2, CYPRESS_MGCGTTLOCAL2_DFLT);
		WREG32_CG(CG_CGTT_LOCAL_3, CYPRESS_MGCGTTLOCAL3_DFLT);

		if (pi->mgcgtssm)
			WREG32(CGTS_SM_CTRL_REG, cgts_sm_ctrl_reg);

		if (eg_pi->mcls) {
			WREG32_P(MC_CITF_MISC_RD_CG, MEM_LS_ENABLE, ~MEM_LS_ENABLE);
			WREG32_P(MC_CITF_MISC_WR_CG, MEM_LS_ENABLE, ~MEM_LS_ENABLE);
			WREG32_P(MC_CITF_MISC_VM_CG, MEM_LS_ENABLE, ~MEM_LS_ENABLE);
			WREG32_P(MC_HUB_MISC_HUB_CG, MEM_LS_ENABLE, ~MEM_LS_ENABLE);
			WREG32_P(MC_HUB_MISC_VM_CG, MEM_LS_ENABLE, ~MEM_LS_ENABLE);
			WREG32_P(MC_HUB_MISC_SIP_CG, MEM_LS_ENABLE, ~MEM_LS_ENABLE);
			WREG32_P(MC_XPB_CLK_GAT, MEM_LS_ENABLE, ~MEM_LS_ENABLE);
			WREG32_P(VM_L2_CG, MEM_LS_ENABLE, ~MEM_LS_ENABLE);
		}
	} else {
		WREG32(GRBM_GFX_INDEX, 0xC0000000);

		WREG32_CG(CG_CGTT_LOCAL_0, 0xFFFFFFFF);
		WREG32_CG(CG_CGTT_LOCAL_1, 0xFFFFFFFF);
		WREG32_CG(CG_CGTT_LOCAL_2, 0xFFFFFFFF);
		WREG32_CG(CG_CGTT_LOCAL_3, 0xFFFFFFFF);

		if (pi->mgcgtssm)
			WREG32(CGTS_SM_CTRL_REG, 0x81f44bc0);
	}
}