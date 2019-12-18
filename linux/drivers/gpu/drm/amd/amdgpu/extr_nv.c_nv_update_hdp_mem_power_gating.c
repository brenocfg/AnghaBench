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
typedef  int /*<<< orphan*/  uint32_t ;
struct amdgpu_device {int cg_flags; } ;

/* Variables and functions */
 int AMD_CG_SUPPORT_HDP_DS ; 
 int AMD_CG_SUPPORT_HDP_LS ; 
 int AMD_CG_SUPPORT_HDP_SD ; 
 int /*<<< orphan*/  HDP ; 
 int /*<<< orphan*/  HDP_CLK_CNTL ; 
 int /*<<< orphan*/  HDP_MEM_POWER_CTRL ; 
 int /*<<< orphan*/  IPH_MEM_CLK_SOFT_OVERRIDE ; 
 int /*<<< orphan*/  IPH_MEM_POWER_CTRL_EN ; 
 int /*<<< orphan*/  IPH_MEM_POWER_DS_EN ; 
 int /*<<< orphan*/  IPH_MEM_POWER_LS_EN ; 
 int /*<<< orphan*/  IPH_MEM_POWER_SD_EN ; 
 int /*<<< orphan*/  RC_MEM_CLK_SOFT_OVERRIDE ; 
 int /*<<< orphan*/  RC_MEM_POWER_CTRL_EN ; 
 int /*<<< orphan*/  RC_MEM_POWER_DS_EN ; 
 int /*<<< orphan*/  RC_MEM_POWER_LS_EN ; 
 int /*<<< orphan*/  RC_MEM_POWER_SD_EN ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmHDP_CLK_CNTL ; 
 int /*<<< orphan*/  mmHDP_MEM_POWER_CTRL ; 

__attribute__((used)) static void nv_update_hdp_mem_power_gating(struct amdgpu_device *adev,
					   bool enable)
{
	uint32_t hdp_clk_cntl, hdp_clk_cntl1;
	uint32_t hdp_mem_pwr_cntl;

	if (!(adev->cg_flags & (AMD_CG_SUPPORT_HDP_LS |
				AMD_CG_SUPPORT_HDP_DS |
				AMD_CG_SUPPORT_HDP_SD)))
		return;

	hdp_clk_cntl = hdp_clk_cntl1 = RREG32_SOC15(HDP, 0, mmHDP_CLK_CNTL);
	hdp_mem_pwr_cntl = RREG32_SOC15(HDP, 0, mmHDP_MEM_POWER_CTRL);

	/* Before doing clock/power mode switch,
	 * forced on IPH & RC clock */
	hdp_clk_cntl = REG_SET_FIELD(hdp_clk_cntl, HDP_CLK_CNTL,
				     IPH_MEM_CLK_SOFT_OVERRIDE, 1);
	hdp_clk_cntl = REG_SET_FIELD(hdp_clk_cntl, HDP_CLK_CNTL,
				     RC_MEM_CLK_SOFT_OVERRIDE, 1);
	WREG32_SOC15(HDP, 0, mmHDP_CLK_CNTL, hdp_clk_cntl);

	/* HDP 5.0 doesn't support dynamic power mode switch,
	 * disable clock and power gating before any changing */
	hdp_mem_pwr_cntl = REG_SET_FIELD(hdp_mem_pwr_cntl, HDP_MEM_POWER_CTRL,
					 IPH_MEM_POWER_CTRL_EN, 0);
	hdp_mem_pwr_cntl = REG_SET_FIELD(hdp_mem_pwr_cntl, HDP_MEM_POWER_CTRL,
					 IPH_MEM_POWER_LS_EN, 0);
	hdp_mem_pwr_cntl = REG_SET_FIELD(hdp_mem_pwr_cntl, HDP_MEM_POWER_CTRL,
					 IPH_MEM_POWER_DS_EN, 0);
	hdp_mem_pwr_cntl = REG_SET_FIELD(hdp_mem_pwr_cntl, HDP_MEM_POWER_CTRL,
					 IPH_MEM_POWER_SD_EN, 0);
	hdp_mem_pwr_cntl = REG_SET_FIELD(hdp_mem_pwr_cntl, HDP_MEM_POWER_CTRL,
					 RC_MEM_POWER_CTRL_EN, 0);
	hdp_mem_pwr_cntl = REG_SET_FIELD(hdp_mem_pwr_cntl, HDP_MEM_POWER_CTRL,
					 RC_MEM_POWER_LS_EN, 0);
	hdp_mem_pwr_cntl = REG_SET_FIELD(hdp_mem_pwr_cntl, HDP_MEM_POWER_CTRL,
					 RC_MEM_POWER_DS_EN, 0);
	hdp_mem_pwr_cntl = REG_SET_FIELD(hdp_mem_pwr_cntl, HDP_MEM_POWER_CTRL,
					 RC_MEM_POWER_SD_EN, 0);
	WREG32_SOC15(HDP, 0, mmHDP_MEM_POWER_CTRL, hdp_mem_pwr_cntl);

	/* only one clock gating mode (LS/DS/SD) can be enabled */
	if (adev->cg_flags & AMD_CG_SUPPORT_HDP_LS) {
		hdp_mem_pwr_cntl = REG_SET_FIELD(hdp_mem_pwr_cntl,
						 HDP_MEM_POWER_CTRL,
						 IPH_MEM_POWER_LS_EN, enable);
		hdp_mem_pwr_cntl = REG_SET_FIELD(hdp_mem_pwr_cntl,
						 HDP_MEM_POWER_CTRL,
						 RC_MEM_POWER_LS_EN, enable);
	} else if (adev->cg_flags & AMD_CG_SUPPORT_HDP_DS) {
		hdp_mem_pwr_cntl = REG_SET_FIELD(hdp_mem_pwr_cntl,
						 HDP_MEM_POWER_CTRL,
						 IPH_MEM_POWER_DS_EN, enable);
		hdp_mem_pwr_cntl = REG_SET_FIELD(hdp_mem_pwr_cntl,
						 HDP_MEM_POWER_CTRL,
						 RC_MEM_POWER_DS_EN, enable);
	} else if (adev->cg_flags & AMD_CG_SUPPORT_HDP_SD) {
		hdp_mem_pwr_cntl = REG_SET_FIELD(hdp_mem_pwr_cntl,
						 HDP_MEM_POWER_CTRL,
						 IPH_MEM_POWER_SD_EN, enable);
		/* RC should not use shut down mode, fallback to ds */
		hdp_mem_pwr_cntl = REG_SET_FIELD(hdp_mem_pwr_cntl,
						 HDP_MEM_POWER_CTRL,
						 RC_MEM_POWER_DS_EN, enable);
	}

	WREG32_SOC15(HDP, 0, mmHDP_MEM_POWER_CTRL, hdp_mem_pwr_cntl);

	/* restore IPH & RC clock override after clock/power mode changing */
	WREG32_SOC15(HDP, 0, mmHDP_CLK_CNTL, hdp_clk_cntl1);
}