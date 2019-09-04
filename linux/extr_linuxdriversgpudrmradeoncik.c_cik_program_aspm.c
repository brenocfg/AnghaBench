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
struct radeon_device {int flags; TYPE_1__* pdev; } ;
struct pci_dev {int dummy; } ;
struct TYPE_4__ {struct pci_dev* self; } ;
struct TYPE_3__ {TYPE_2__* bus; } ;

/* Variables and functions */
 int BCLK_AS_XCLK ; 
 int /*<<< orphan*/  CG_CLKPIN_CNTL ; 
 int /*<<< orphan*/  CG_CLKPIN_CNTL_2 ; 
 int CMON_CLK_SEL (int) ; 
 int CMON_CLK_SEL_MASK ; 
 int DEEP_SLEEP_CLK_SEL (int) ; 
 int DEEP_SLEEP_CLK_SEL_MASK ; 
 int FORCE_BIF_REFCLK_EN ; 
 int LC_ALLOW_PDWN_IN_L1 ; 
 int LC_ALLOW_PDWN_IN_L23 ; 
 int LC_DYN_LANES_PWR_STATE (int) ; 
 int LC_DYN_LANES_PWR_STATE_MASK ; 
 int LC_GO_TO_RECOVERY ; 
 int LC_L0S_INACTIVITY (int) ; 
 int LC_L0S_INACTIVITY_MASK ; 
 int LC_L1_INACTIVITY (int) ; 
 int LC_L1_INACTIVITY_MASK ; 
 int LC_N_FTS_MASK ; 
 int LC_PMI_TO_L1_DIS ; 
 int LC_REVERSE_RCVR ; 
 int LC_REVERSE_XMIT ; 
 int LC_XMIT_N_FTS (int) ; 
 int LC_XMIT_N_FTS_MASK ; 
 int LC_XMIT_N_FTS_OVERRIDE_EN ; 
 int /*<<< orphan*/  MISC_CLK_CTRL ; 
 int /*<<< orphan*/  MPLL_BYPASSCLK_SEL ; 
 int MPLL_CLKOUT_SEL (int) ; 
 int MPLL_CLKOUT_SEL_MASK ; 
 int MST_MEM_LS_EN ; 
 int /*<<< orphan*/  PB0_PIF_PWRDOWN_0 ; 
 int /*<<< orphan*/  PB0_PIF_PWRDOWN_1 ; 
 int /*<<< orphan*/  PB1_PIF_PWRDOWN_0 ; 
 int /*<<< orphan*/  PB1_PIF_PWRDOWN_1 ; 
 int /*<<< orphan*/  PCIE_CNTL2 ; 
 int /*<<< orphan*/  PCIE_LC_CNTL ; 
 int /*<<< orphan*/  PCIE_LC_CNTL2 ; 
 int /*<<< orphan*/  PCIE_LC_CNTL3 ; 
 int /*<<< orphan*/  PCIE_LC_LINK_WIDTH_CNTL ; 
 int /*<<< orphan*/  PCIE_LC_N_FTS_CNTL ; 
 int /*<<< orphan*/  PCIE_LC_STATUS1 ; 
 int /*<<< orphan*/  PCIE_P_CNTL ; 
 int /*<<< orphan*/  PCI_EXP_LNKCAP ; 
 int PCI_EXP_LNKCAP_CLKPM ; 
 int PLL_POWER_STATE_IN_OFF_0 (int) ; 
 int PLL_POWER_STATE_IN_OFF_0_MASK ; 
 int PLL_POWER_STATE_IN_OFF_1 (int) ; 
 int PLL_POWER_STATE_IN_OFF_1_MASK ; 
 int PLL_POWER_STATE_IN_TXS2_0 (int) ; 
 int PLL_POWER_STATE_IN_TXS2_0_MASK ; 
 int PLL_POWER_STATE_IN_TXS2_1 (int) ; 
 int PLL_POWER_STATE_IN_TXS2_1_MASK ; 
 int P_IGNORE_EDB_ERR ; 
 int RADEON_IS_IGP ; 
 int RADEON_IS_PCIE ; 
 int REPLAY_MEM_LS_EN ; 
 int RREG32_PCIE_PORT (int /*<<< orphan*/ ) ; 
 int RREG32_SMC (int /*<<< orphan*/ ) ; 
 int SLV_MEM_LS_EN ; 
 int /*<<< orphan*/  THM_CLK_CNTL ; 
 int TMON_CLK_SEL (int) ; 
 int TMON_CLK_SEL_MASK ; 
 int /*<<< orphan*/  WREG32_PCIE_PORT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_SMC (int /*<<< orphan*/ ,int) ; 
 int ZCLK_SEL (int) ; 
 int ZCLK_SEL_MASK ; 
 int /*<<< orphan*/  pci_is_root_bus (TYPE_2__*) ; 
 int /*<<< orphan*/  pcie_capability_read_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ radeon_aspm ; 

__attribute__((used)) static void cik_program_aspm(struct radeon_device *rdev)
{
	u32 data, orig;
	bool disable_l0s = false, disable_l1 = false, disable_plloff_in_l1 = false;
	bool disable_clkreq = false;

	if (radeon_aspm == 0)
		return;

	/* XXX double check IGPs */
	if (rdev->flags & RADEON_IS_IGP)
		return;

	if (!(rdev->flags & RADEON_IS_PCIE))
		return;

	orig = data = RREG32_PCIE_PORT(PCIE_LC_N_FTS_CNTL);
	data &= ~LC_XMIT_N_FTS_MASK;
	data |= LC_XMIT_N_FTS(0x24) | LC_XMIT_N_FTS_OVERRIDE_EN;
	if (orig != data)
		WREG32_PCIE_PORT(PCIE_LC_N_FTS_CNTL, data);

	orig = data = RREG32_PCIE_PORT(PCIE_LC_CNTL3);
	data |= LC_GO_TO_RECOVERY;
	if (orig != data)
		WREG32_PCIE_PORT(PCIE_LC_CNTL3, data);

	orig = data = RREG32_PCIE_PORT(PCIE_P_CNTL);
	data |= P_IGNORE_EDB_ERR;
	if (orig != data)
		WREG32_PCIE_PORT(PCIE_P_CNTL, data);

	orig = data = RREG32_PCIE_PORT(PCIE_LC_CNTL);
	data &= ~(LC_L0S_INACTIVITY_MASK | LC_L1_INACTIVITY_MASK);
	data |= LC_PMI_TO_L1_DIS;
	if (!disable_l0s)
		data |= LC_L0S_INACTIVITY(7);

	if (!disable_l1) {
		data |= LC_L1_INACTIVITY(7);
		data &= ~LC_PMI_TO_L1_DIS;
		if (orig != data)
			WREG32_PCIE_PORT(PCIE_LC_CNTL, data);

		if (!disable_plloff_in_l1) {
			bool clk_req_support;

			orig = data = RREG32_PCIE_PORT(PB0_PIF_PWRDOWN_0);
			data &= ~(PLL_POWER_STATE_IN_OFF_0_MASK | PLL_POWER_STATE_IN_TXS2_0_MASK);
			data |= PLL_POWER_STATE_IN_OFF_0(7) | PLL_POWER_STATE_IN_TXS2_0(7);
			if (orig != data)
				WREG32_PCIE_PORT(PB0_PIF_PWRDOWN_0, data);

			orig = data = RREG32_PCIE_PORT(PB0_PIF_PWRDOWN_1);
			data &= ~(PLL_POWER_STATE_IN_OFF_1_MASK | PLL_POWER_STATE_IN_TXS2_1_MASK);
			data |= PLL_POWER_STATE_IN_OFF_1(7) | PLL_POWER_STATE_IN_TXS2_1(7);
			if (orig != data)
				WREG32_PCIE_PORT(PB0_PIF_PWRDOWN_1, data);

			orig = data = RREG32_PCIE_PORT(PB1_PIF_PWRDOWN_0);
			data &= ~(PLL_POWER_STATE_IN_OFF_0_MASK | PLL_POWER_STATE_IN_TXS2_0_MASK);
			data |= PLL_POWER_STATE_IN_OFF_0(7) | PLL_POWER_STATE_IN_TXS2_0(7);
			if (orig != data)
				WREG32_PCIE_PORT(PB1_PIF_PWRDOWN_0, data);

			orig = data = RREG32_PCIE_PORT(PB1_PIF_PWRDOWN_1);
			data &= ~(PLL_POWER_STATE_IN_OFF_1_MASK | PLL_POWER_STATE_IN_TXS2_1_MASK);
			data |= PLL_POWER_STATE_IN_OFF_1(7) | PLL_POWER_STATE_IN_TXS2_1(7);
			if (orig != data)
				WREG32_PCIE_PORT(PB1_PIF_PWRDOWN_1, data);

			orig = data = RREG32_PCIE_PORT(PCIE_LC_LINK_WIDTH_CNTL);
			data &= ~LC_DYN_LANES_PWR_STATE_MASK;
			data |= LC_DYN_LANES_PWR_STATE(3);
			if (orig != data)
				WREG32_PCIE_PORT(PCIE_LC_LINK_WIDTH_CNTL, data);

			if (!disable_clkreq &&
			    !pci_is_root_bus(rdev->pdev->bus)) {
				struct pci_dev *root = rdev->pdev->bus->self;
				u32 lnkcap;

				clk_req_support = false;
				pcie_capability_read_dword(root, PCI_EXP_LNKCAP, &lnkcap);
				if (lnkcap & PCI_EXP_LNKCAP_CLKPM)
					clk_req_support = true;
			} else {
				clk_req_support = false;
			}

			if (clk_req_support) {
				orig = data = RREG32_PCIE_PORT(PCIE_LC_CNTL2);
				data |= LC_ALLOW_PDWN_IN_L1 | LC_ALLOW_PDWN_IN_L23;
				if (orig != data)
					WREG32_PCIE_PORT(PCIE_LC_CNTL2, data);

				orig = data = RREG32_SMC(THM_CLK_CNTL);
				data &= ~(CMON_CLK_SEL_MASK | TMON_CLK_SEL_MASK);
				data |= CMON_CLK_SEL(1) | TMON_CLK_SEL(1);
				if (orig != data)
					WREG32_SMC(THM_CLK_CNTL, data);

				orig = data = RREG32_SMC(MISC_CLK_CTRL);
				data &= ~(DEEP_SLEEP_CLK_SEL_MASK | ZCLK_SEL_MASK);
				data |= DEEP_SLEEP_CLK_SEL(1) | ZCLK_SEL(1);
				if (orig != data)
					WREG32_SMC(MISC_CLK_CTRL, data);

				orig = data = RREG32_SMC(CG_CLKPIN_CNTL);
				data &= ~BCLK_AS_XCLK;
				if (orig != data)
					WREG32_SMC(CG_CLKPIN_CNTL, data);

				orig = data = RREG32_SMC(CG_CLKPIN_CNTL_2);
				data &= ~FORCE_BIF_REFCLK_EN;
				if (orig != data)
					WREG32_SMC(CG_CLKPIN_CNTL_2, data);

				orig = data = RREG32_SMC(MPLL_BYPASSCLK_SEL);
				data &= ~MPLL_CLKOUT_SEL_MASK;
				data |= MPLL_CLKOUT_SEL(4);
				if (orig != data)
					WREG32_SMC(MPLL_BYPASSCLK_SEL, data);
			}
		}
	} else {
		if (orig != data)
			WREG32_PCIE_PORT(PCIE_LC_CNTL, data);
	}

	orig = data = RREG32_PCIE_PORT(PCIE_CNTL2);
	data |= SLV_MEM_LS_EN | MST_MEM_LS_EN | REPLAY_MEM_LS_EN;
	if (orig != data)
		WREG32_PCIE_PORT(PCIE_CNTL2, data);

	if (!disable_l0s) {
		data = RREG32_PCIE_PORT(PCIE_LC_N_FTS_CNTL);
		if((data & LC_N_FTS_MASK) == LC_N_FTS_MASK) {
			data = RREG32_PCIE_PORT(PCIE_LC_STATUS1);
			if ((data & LC_REVERSE_XMIT) && (data & LC_REVERSE_RCVR)) {
				orig = data = RREG32_PCIE_PORT(PCIE_LC_CNTL);
				data &= ~LC_L0S_INACTIVITY_MASK;
				if (orig != data)
					WREG32_PCIE_PORT(PCIE_LC_CNTL, data);
			}
		}
	}
}