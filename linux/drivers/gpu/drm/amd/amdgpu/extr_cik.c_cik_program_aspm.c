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
typedef  int u32 ;
struct pci_dev {int dummy; } ;
struct amdgpu_device {int flags; TYPE_1__* pdev; } ;
struct TYPE_4__ {struct pci_dev* self; } ;
struct TYPE_3__ {TYPE_2__* bus; } ;

/* Variables and functions */
 int AMD_IS_APU ; 
 int CG_CLKPIN_CNTL_2__FORCE_BIF_REFCLK_EN_MASK ; 
 int CG_CLKPIN_CNTL__BCLK_AS_XCLK_MASK ; 
 int MISC_CLK_CTRL__DEEP_SLEEP_CLK_SEL_MASK ; 
 int MISC_CLK_CTRL__DEEP_SLEEP_CLK_SEL__SHIFT ; 
 int MISC_CLK_CTRL__ZCLK_SEL_MASK ; 
 int MISC_CLK_CTRL__ZCLK_SEL__SHIFT ; 
 int MPLL_BYPASSCLK_SEL__MPLL_CLKOUT_SEL_MASK ; 
 int MPLL_BYPASSCLK_SEL__MPLL_CLKOUT_SEL__SHIFT ; 
 int PB0_PIF_PWRDOWN_0__PLL_POWER_STATE_IN_OFF_0_MASK ; 
 int PB0_PIF_PWRDOWN_0__PLL_POWER_STATE_IN_OFF_0__SHIFT ; 
 int PB0_PIF_PWRDOWN_0__PLL_POWER_STATE_IN_TXS2_0_MASK ; 
 int PB0_PIF_PWRDOWN_0__PLL_POWER_STATE_IN_TXS2_0__SHIFT ; 
 int PB0_PIF_PWRDOWN_1__PLL_POWER_STATE_IN_OFF_1_MASK ; 
 int PB0_PIF_PWRDOWN_1__PLL_POWER_STATE_IN_OFF_1__SHIFT ; 
 int PB0_PIF_PWRDOWN_1__PLL_POWER_STATE_IN_TXS2_1_MASK ; 
 int PB0_PIF_PWRDOWN_1__PLL_POWER_STATE_IN_TXS2_1__SHIFT ; 
 int PB1_PIF_PWRDOWN_0__PLL_POWER_STATE_IN_OFF_0_MASK ; 
 int PB1_PIF_PWRDOWN_0__PLL_POWER_STATE_IN_OFF_0__SHIFT ; 
 int PB1_PIF_PWRDOWN_0__PLL_POWER_STATE_IN_TXS2_0_MASK ; 
 int PB1_PIF_PWRDOWN_0__PLL_POWER_STATE_IN_TXS2_0__SHIFT ; 
 int PB1_PIF_PWRDOWN_1__PLL_POWER_STATE_IN_OFF_1_MASK ; 
 int PB1_PIF_PWRDOWN_1__PLL_POWER_STATE_IN_OFF_1__SHIFT ; 
 int PB1_PIF_PWRDOWN_1__PLL_POWER_STATE_IN_TXS2_1_MASK ; 
 int PB1_PIF_PWRDOWN_1__PLL_POWER_STATE_IN_TXS2_1__SHIFT ; 
 int PCIE_CNTL2__MST_MEM_LS_EN_MASK ; 
 int PCIE_CNTL2__REPLAY_MEM_LS_EN_MASK ; 
 int PCIE_CNTL2__SLV_MEM_LS_EN_MASK ; 
 int PCIE_LC_CNTL2__LC_ALLOW_PDWN_IN_L1_MASK ; 
 int PCIE_LC_CNTL2__LC_ALLOW_PDWN_IN_L23_MASK ; 
 int PCIE_LC_CNTL3__LC_GO_TO_RECOVERY_MASK ; 
 int PCIE_LC_CNTL__LC_L0S_INACTIVITY_MASK ; 
 int PCIE_LC_CNTL__LC_L0S_INACTIVITY__SHIFT ; 
 int PCIE_LC_CNTL__LC_L1_INACTIVITY_MASK ; 
 int PCIE_LC_CNTL__LC_L1_INACTIVITY__SHIFT ; 
 int PCIE_LC_CNTL__LC_PMI_TO_L1_DIS_MASK ; 
 int PCIE_LC_LINK_WIDTH_CNTL__LC_DYN_LANES_PWR_STATE_MASK ; 
 int PCIE_LC_LINK_WIDTH_CNTL__LC_DYN_LANES_PWR_STATE__SHIFT ; 
 int PCIE_LC_N_FTS_CNTL__LC_N_FTS_MASK ; 
 int PCIE_LC_N_FTS_CNTL__LC_XMIT_N_FTS_MASK ; 
 int PCIE_LC_N_FTS_CNTL__LC_XMIT_N_FTS_OVERRIDE_EN_MASK ; 
 int PCIE_LC_N_FTS_CNTL__LC_XMIT_N_FTS__SHIFT ; 
 int PCIE_LC_STATUS1__LC_REVERSE_RCVR_MASK ; 
 int PCIE_LC_STATUS1__LC_REVERSE_XMIT_MASK ; 
 int PCIE_P_CNTL__P_IGNORE_EDB_ERR_MASK ; 
 int /*<<< orphan*/  PCI_EXP_LNKCAP ; 
 int PCI_EXP_LNKCAP_CLKPM ; 
 int RREG32_PCIE (int /*<<< orphan*/ ) ; 
 int RREG32_SMC (int /*<<< orphan*/ ) ; 
 int THM_CLK_CNTL__CMON_CLK_SEL_MASK ; 
 int THM_CLK_CNTL__CMON_CLK_SEL__SHIFT ; 
 int THM_CLK_CNTL__TMON_CLK_SEL_MASK ; 
 int THM_CLK_CNTL__TMON_CLK_SEL__SHIFT ; 
 int /*<<< orphan*/  WREG32_PCIE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_SMC (int /*<<< orphan*/ ,int) ; 
 scalar_t__ amdgpu_aspm ; 
 int /*<<< orphan*/  ixCG_CLKPIN_CNTL ; 
 int /*<<< orphan*/  ixCG_CLKPIN_CNTL_2 ; 
 int /*<<< orphan*/  ixMISC_CLK_CTRL ; 
 int /*<<< orphan*/  ixMPLL_BYPASSCLK_SEL ; 
 int /*<<< orphan*/  ixPB0_PIF_PWRDOWN_0 ; 
 int /*<<< orphan*/  ixPB0_PIF_PWRDOWN_1 ; 
 int /*<<< orphan*/  ixPB1_PIF_PWRDOWN_0 ; 
 int /*<<< orphan*/  ixPB1_PIF_PWRDOWN_1 ; 
 int /*<<< orphan*/  ixPCIE_CNTL2 ; 
 int /*<<< orphan*/  ixPCIE_LC_CNTL ; 
 int /*<<< orphan*/  ixPCIE_LC_CNTL2 ; 
 int /*<<< orphan*/  ixPCIE_LC_CNTL3 ; 
 int /*<<< orphan*/  ixPCIE_LC_LINK_WIDTH_CNTL ; 
 int /*<<< orphan*/  ixPCIE_LC_N_FTS_CNTL ; 
 int /*<<< orphan*/  ixPCIE_LC_STATUS1 ; 
 int /*<<< orphan*/  ixPCIE_P_CNTL ; 
 int /*<<< orphan*/  ixTHM_CLK_CNTL ; 
 scalar_t__ pci_is_root_bus (TYPE_2__*) ; 
 int /*<<< orphan*/  pcie_capability_read_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void cik_program_aspm(struct amdgpu_device *adev)
{
	u32 data, orig;
	bool disable_l0s = false, disable_l1 = false, disable_plloff_in_l1 = false;
	bool disable_clkreq = false;

	if (amdgpu_aspm == 0)
		return;

	if (pci_is_root_bus(adev->pdev->bus))
		return;

	/* XXX double check APUs */
	if (adev->flags & AMD_IS_APU)
		return;

	orig = data = RREG32_PCIE(ixPCIE_LC_N_FTS_CNTL);
	data &= ~PCIE_LC_N_FTS_CNTL__LC_XMIT_N_FTS_MASK;
	data |= (0x24 << PCIE_LC_N_FTS_CNTL__LC_XMIT_N_FTS__SHIFT) |
		PCIE_LC_N_FTS_CNTL__LC_XMIT_N_FTS_OVERRIDE_EN_MASK;
	if (orig != data)
		WREG32_PCIE(ixPCIE_LC_N_FTS_CNTL, data);

	orig = data = RREG32_PCIE(ixPCIE_LC_CNTL3);
	data |= PCIE_LC_CNTL3__LC_GO_TO_RECOVERY_MASK;
	if (orig != data)
		WREG32_PCIE(ixPCIE_LC_CNTL3, data);

	orig = data = RREG32_PCIE(ixPCIE_P_CNTL);
	data |= PCIE_P_CNTL__P_IGNORE_EDB_ERR_MASK;
	if (orig != data)
		WREG32_PCIE(ixPCIE_P_CNTL, data);

	orig = data = RREG32_PCIE(ixPCIE_LC_CNTL);
	data &= ~(PCIE_LC_CNTL__LC_L0S_INACTIVITY_MASK |
		PCIE_LC_CNTL__LC_L1_INACTIVITY_MASK);
	data |= PCIE_LC_CNTL__LC_PMI_TO_L1_DIS_MASK;
	if (!disable_l0s)
		data |= (7 << PCIE_LC_CNTL__LC_L0S_INACTIVITY__SHIFT);

	if (!disable_l1) {
		data |= (7 << PCIE_LC_CNTL__LC_L1_INACTIVITY__SHIFT);
		data &= ~PCIE_LC_CNTL__LC_PMI_TO_L1_DIS_MASK;
		if (orig != data)
			WREG32_PCIE(ixPCIE_LC_CNTL, data);

		if (!disable_plloff_in_l1) {
			bool clk_req_support;

			orig = data = RREG32_PCIE(ixPB0_PIF_PWRDOWN_0);
			data &= ~(PB0_PIF_PWRDOWN_0__PLL_POWER_STATE_IN_OFF_0_MASK |
				PB0_PIF_PWRDOWN_0__PLL_POWER_STATE_IN_TXS2_0_MASK);
			data |= (7 << PB0_PIF_PWRDOWN_0__PLL_POWER_STATE_IN_OFF_0__SHIFT) |
				(7 << PB0_PIF_PWRDOWN_0__PLL_POWER_STATE_IN_TXS2_0__SHIFT);
			if (orig != data)
				WREG32_PCIE(ixPB0_PIF_PWRDOWN_0, data);

			orig = data = RREG32_PCIE(ixPB0_PIF_PWRDOWN_1);
			data &= ~(PB0_PIF_PWRDOWN_1__PLL_POWER_STATE_IN_OFF_1_MASK |
				PB0_PIF_PWRDOWN_1__PLL_POWER_STATE_IN_TXS2_1_MASK);
			data |= (7 << PB0_PIF_PWRDOWN_1__PLL_POWER_STATE_IN_OFF_1__SHIFT) |
				(7 << PB0_PIF_PWRDOWN_1__PLL_POWER_STATE_IN_TXS2_1__SHIFT);
			if (orig != data)
				WREG32_PCIE(ixPB0_PIF_PWRDOWN_1, data);

			orig = data = RREG32_PCIE(ixPB1_PIF_PWRDOWN_0);
			data &= ~(PB1_PIF_PWRDOWN_0__PLL_POWER_STATE_IN_OFF_0_MASK |
				PB1_PIF_PWRDOWN_0__PLL_POWER_STATE_IN_TXS2_0_MASK);
			data |= (7 << PB1_PIF_PWRDOWN_0__PLL_POWER_STATE_IN_OFF_0__SHIFT) |
				(7 << PB1_PIF_PWRDOWN_0__PLL_POWER_STATE_IN_TXS2_0__SHIFT);
			if (orig != data)
				WREG32_PCIE(ixPB1_PIF_PWRDOWN_0, data);

			orig = data = RREG32_PCIE(ixPB1_PIF_PWRDOWN_1);
			data &= ~(PB1_PIF_PWRDOWN_1__PLL_POWER_STATE_IN_OFF_1_MASK |
				PB1_PIF_PWRDOWN_1__PLL_POWER_STATE_IN_TXS2_1_MASK);
			data |= (7 << PB1_PIF_PWRDOWN_1__PLL_POWER_STATE_IN_OFF_1__SHIFT) |
				(7 << PB1_PIF_PWRDOWN_1__PLL_POWER_STATE_IN_TXS2_1__SHIFT);
			if (orig != data)
				WREG32_PCIE(ixPB1_PIF_PWRDOWN_1, data);

			orig = data = RREG32_PCIE(ixPCIE_LC_LINK_WIDTH_CNTL);
			data &= ~PCIE_LC_LINK_WIDTH_CNTL__LC_DYN_LANES_PWR_STATE_MASK;
			data |= ~(3 << PCIE_LC_LINK_WIDTH_CNTL__LC_DYN_LANES_PWR_STATE__SHIFT);
			if (orig != data)
				WREG32_PCIE(ixPCIE_LC_LINK_WIDTH_CNTL, data);

			if (!disable_clkreq) {
				struct pci_dev *root = adev->pdev->bus->self;
				u32 lnkcap;

				clk_req_support = false;
				pcie_capability_read_dword(root, PCI_EXP_LNKCAP, &lnkcap);
				if (lnkcap & PCI_EXP_LNKCAP_CLKPM)
					clk_req_support = true;
			} else {
				clk_req_support = false;
			}

			if (clk_req_support) {
				orig = data = RREG32_PCIE(ixPCIE_LC_CNTL2);
				data |= PCIE_LC_CNTL2__LC_ALLOW_PDWN_IN_L1_MASK |
					PCIE_LC_CNTL2__LC_ALLOW_PDWN_IN_L23_MASK;
				if (orig != data)
					WREG32_PCIE(ixPCIE_LC_CNTL2, data);

				orig = data = RREG32_SMC(ixTHM_CLK_CNTL);
				data &= ~(THM_CLK_CNTL__CMON_CLK_SEL_MASK |
					THM_CLK_CNTL__TMON_CLK_SEL_MASK);
				data |= (1 << THM_CLK_CNTL__CMON_CLK_SEL__SHIFT) |
					(1 << THM_CLK_CNTL__TMON_CLK_SEL__SHIFT);
				if (orig != data)
					WREG32_SMC(ixTHM_CLK_CNTL, data);

				orig = data = RREG32_SMC(ixMISC_CLK_CTRL);
				data &= ~(MISC_CLK_CTRL__DEEP_SLEEP_CLK_SEL_MASK |
					MISC_CLK_CTRL__ZCLK_SEL_MASK);
				data |= (1 << MISC_CLK_CTRL__DEEP_SLEEP_CLK_SEL__SHIFT) |
					(1 << MISC_CLK_CTRL__ZCLK_SEL__SHIFT);
				if (orig != data)
					WREG32_SMC(ixMISC_CLK_CTRL, data);

				orig = data = RREG32_SMC(ixCG_CLKPIN_CNTL);
				data &= ~CG_CLKPIN_CNTL__BCLK_AS_XCLK_MASK;
				if (orig != data)
					WREG32_SMC(ixCG_CLKPIN_CNTL, data);

				orig = data = RREG32_SMC(ixCG_CLKPIN_CNTL_2);
				data &= ~CG_CLKPIN_CNTL_2__FORCE_BIF_REFCLK_EN_MASK;
				if (orig != data)
					WREG32_SMC(ixCG_CLKPIN_CNTL_2, data);

				orig = data = RREG32_SMC(ixMPLL_BYPASSCLK_SEL);
				data &= ~MPLL_BYPASSCLK_SEL__MPLL_CLKOUT_SEL_MASK;
				data |= (4 << MPLL_BYPASSCLK_SEL__MPLL_CLKOUT_SEL__SHIFT);
				if (orig != data)
					WREG32_SMC(ixMPLL_BYPASSCLK_SEL, data);
			}
		}
	} else {
		if (orig != data)
			WREG32_PCIE(ixPCIE_LC_CNTL, data);
	}

	orig = data = RREG32_PCIE(ixPCIE_CNTL2);
	data |= PCIE_CNTL2__SLV_MEM_LS_EN_MASK |
		PCIE_CNTL2__MST_MEM_LS_EN_MASK |
		PCIE_CNTL2__REPLAY_MEM_LS_EN_MASK;
	if (orig != data)
		WREG32_PCIE(ixPCIE_CNTL2, data);

	if (!disable_l0s) {
		data = RREG32_PCIE(ixPCIE_LC_N_FTS_CNTL);
		if ((data & PCIE_LC_N_FTS_CNTL__LC_N_FTS_MASK) ==
				PCIE_LC_N_FTS_CNTL__LC_N_FTS_MASK) {
			data = RREG32_PCIE(ixPCIE_LC_STATUS1);
			if ((data & PCIE_LC_STATUS1__LC_REVERSE_XMIT_MASK) &&
			(data & PCIE_LC_STATUS1__LC_REVERSE_RCVR_MASK)) {
				orig = data = RREG32_PCIE(ixPCIE_LC_CNTL);
				data &= ~PCIE_LC_CNTL__LC_L0S_INACTIVITY_MASK;
				if (orig != data)
					WREG32_PCIE(ixPCIE_LC_CNTL, data);
			}
		}
	}
}