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
struct amdgpu_device {int flags; scalar_t__ asic_type; TYPE_1__* pdev; } ;
struct TYPE_4__ {struct pci_dev* self; } ;
struct TYPE_3__ {TYPE_2__* bus; } ;

/* Variables and functions */
 int AMD_IS_APU ; 
 int BCLK_AS_XCLK ; 
 int /*<<< orphan*/  CG_CLKPIN_CNTL ; 
 int /*<<< orphan*/  CG_CLKPIN_CNTL_2 ; 
 scalar_t__ CHIP_HAINAN ; 
 scalar_t__ CHIP_OLAND ; 
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
 int LS2_EXIT_TIME (int) ; 
 int LS2_EXIT_TIME_MASK ; 
 int /*<<< orphan*/  MISC_CLK_CNTL ; 
 int /*<<< orphan*/  MPLL_BYPASSCLK_SEL ; 
 int MPLL_CLKOUT_SEL (int) ; 
 int MPLL_CLKOUT_SEL_MASK ; 
 int MST_MEM_LS_EN ; 
 int /*<<< orphan*/  PB0_PIF_CNTL ; 
 int /*<<< orphan*/  PB0_PIF_PWRDOWN_0 ; 
 int /*<<< orphan*/  PB0_PIF_PWRDOWN_1 ; 
 int /*<<< orphan*/  PB0_PIF_PWRDOWN_2 ; 
 int /*<<< orphan*/  PB0_PIF_PWRDOWN_3 ; 
 int /*<<< orphan*/  PB1_PIF_CNTL ; 
 int /*<<< orphan*/  PB1_PIF_PWRDOWN_0 ; 
 int /*<<< orphan*/  PB1_PIF_PWRDOWN_1 ; 
 int /*<<< orphan*/  PB1_PIF_PWRDOWN_2 ; 
 int /*<<< orphan*/  PB1_PIF_PWRDOWN_3 ; 
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
 int PLL_RAMP_UP_TIME_0_MASK ; 
 int PLL_RAMP_UP_TIME_1_MASK ; 
 int PLL_RAMP_UP_TIME_2_MASK ; 
 int PLL_RAMP_UP_TIME_3_MASK ; 
 int P_IGNORE_EDB_ERR ; 
 int REPLAY_MEM_LS_EN ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int RREG32_PCIE (int /*<<< orphan*/ ) ; 
 int RREG32_PCIE_PORT (int /*<<< orphan*/ ) ; 
 int SLV_MEM_LS_EN ; 
 int /*<<< orphan*/  SPLL_CNTL_MODE ; 
 int SPLL_REFCLK_SEL_MASK ; 
 int /*<<< orphan*/  THM_CLK_CNTL ; 
 int TMON_CLK_SEL (int) ; 
 int TMON_CLK_SEL_MASK ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_PCIE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_PCIE_PORT (int /*<<< orphan*/ ,int) ; 
 int ZCLK_SEL (int) ; 
 int ZCLK_SEL_MASK ; 
 scalar_t__ amdgpu_aspm ; 
 int /*<<< orphan*/  pci_is_root_bus (TYPE_2__*) ; 
 int /*<<< orphan*/  pcie_capability_read_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int si_pif_phy0_rreg (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  si_pif_phy0_wreg (struct amdgpu_device*,int /*<<< orphan*/ ,int) ; 
 int si_pif_phy1_rreg (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  si_pif_phy1_wreg (struct amdgpu_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void si_program_aspm(struct amdgpu_device *adev)
{
	u32 data, orig;
	bool disable_l0s = false, disable_l1 = false, disable_plloff_in_l1 = false;
	bool disable_clkreq = false;

	if (amdgpu_aspm == 0)
		return;

	if (adev->flags & AMD_IS_APU)
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

	orig = data = RREG32_PCIE(PCIE_P_CNTL);
	data |= P_IGNORE_EDB_ERR;
	if (orig != data)
		WREG32_PCIE(PCIE_P_CNTL, data);

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

			orig = data = si_pif_phy0_rreg(adev,PB0_PIF_PWRDOWN_0);
			data &= ~(PLL_POWER_STATE_IN_OFF_0_MASK | PLL_POWER_STATE_IN_TXS2_0_MASK);
			data |= PLL_POWER_STATE_IN_OFF_0(7) | PLL_POWER_STATE_IN_TXS2_0(7);
			if (orig != data)
				si_pif_phy0_wreg(adev,PB0_PIF_PWRDOWN_0, data);

			orig = data = si_pif_phy0_rreg(adev,PB0_PIF_PWRDOWN_1);
			data &= ~(PLL_POWER_STATE_IN_OFF_1_MASK | PLL_POWER_STATE_IN_TXS2_1_MASK);
			data |= PLL_POWER_STATE_IN_OFF_1(7) | PLL_POWER_STATE_IN_TXS2_1(7);
			if (orig != data)
				si_pif_phy0_wreg(adev,PB0_PIF_PWRDOWN_1, data);

			orig = data = si_pif_phy1_rreg(adev,PB1_PIF_PWRDOWN_0);
			data &= ~(PLL_POWER_STATE_IN_OFF_0_MASK | PLL_POWER_STATE_IN_TXS2_0_MASK);
			data |= PLL_POWER_STATE_IN_OFF_0(7) | PLL_POWER_STATE_IN_TXS2_0(7);
			if (orig != data)
				si_pif_phy1_wreg(adev,PB1_PIF_PWRDOWN_0, data);

			orig = data = si_pif_phy1_rreg(adev,PB1_PIF_PWRDOWN_1);
			data &= ~(PLL_POWER_STATE_IN_OFF_1_MASK | PLL_POWER_STATE_IN_TXS2_1_MASK);
			data |= PLL_POWER_STATE_IN_OFF_1(7) | PLL_POWER_STATE_IN_TXS2_1(7);
			if (orig != data)
				si_pif_phy1_wreg(adev,PB1_PIF_PWRDOWN_1, data);

			if ((adev->asic_type != CHIP_OLAND) && (adev->asic_type != CHIP_HAINAN)) {
				orig = data = si_pif_phy0_rreg(adev,PB0_PIF_PWRDOWN_0);
				data &= ~PLL_RAMP_UP_TIME_0_MASK;
				if (orig != data)
					si_pif_phy0_wreg(adev,PB0_PIF_PWRDOWN_0, data);

				orig = data = si_pif_phy0_rreg(adev,PB0_PIF_PWRDOWN_1);
				data &= ~PLL_RAMP_UP_TIME_1_MASK;
				if (orig != data)
					si_pif_phy0_wreg(adev,PB0_PIF_PWRDOWN_1, data);

				orig = data = si_pif_phy0_rreg(adev,PB0_PIF_PWRDOWN_2);
				data &= ~PLL_RAMP_UP_TIME_2_MASK;
				if (orig != data)
					si_pif_phy0_wreg(adev,PB0_PIF_PWRDOWN_2, data);

				orig = data = si_pif_phy0_rreg(adev,PB0_PIF_PWRDOWN_3);
				data &= ~PLL_RAMP_UP_TIME_3_MASK;
				if (orig != data)
					si_pif_phy0_wreg(adev,PB0_PIF_PWRDOWN_3, data);

				orig = data = si_pif_phy1_rreg(adev,PB1_PIF_PWRDOWN_0);
				data &= ~PLL_RAMP_UP_TIME_0_MASK;
				if (orig != data)
					si_pif_phy1_wreg(adev,PB1_PIF_PWRDOWN_0, data);

				orig = data = si_pif_phy1_rreg(adev,PB1_PIF_PWRDOWN_1);
				data &= ~PLL_RAMP_UP_TIME_1_MASK;
				if (orig != data)
					si_pif_phy1_wreg(adev,PB1_PIF_PWRDOWN_1, data);

				orig = data = si_pif_phy1_rreg(adev,PB1_PIF_PWRDOWN_2);
				data &= ~PLL_RAMP_UP_TIME_2_MASK;
				if (orig != data)
					si_pif_phy1_wreg(adev,PB1_PIF_PWRDOWN_2, data);

				orig = data = si_pif_phy1_rreg(adev,PB1_PIF_PWRDOWN_3);
				data &= ~PLL_RAMP_UP_TIME_3_MASK;
				if (orig != data)
					si_pif_phy1_wreg(adev,PB1_PIF_PWRDOWN_3, data);
			}
			orig = data = RREG32_PCIE_PORT(PCIE_LC_LINK_WIDTH_CNTL);
			data &= ~LC_DYN_LANES_PWR_STATE_MASK;
			data |= LC_DYN_LANES_PWR_STATE(3);
			if (orig != data)
				WREG32_PCIE_PORT(PCIE_LC_LINK_WIDTH_CNTL, data);

			orig = data = si_pif_phy0_rreg(adev,PB0_PIF_CNTL);
			data &= ~LS2_EXIT_TIME_MASK;
			if ((adev->asic_type == CHIP_OLAND) || (adev->asic_type == CHIP_HAINAN))
				data |= LS2_EXIT_TIME(5);
			if (orig != data)
				si_pif_phy0_wreg(adev,PB0_PIF_CNTL, data);

			orig = data = si_pif_phy1_rreg(adev,PB1_PIF_CNTL);
			data &= ~LS2_EXIT_TIME_MASK;
			if ((adev->asic_type == CHIP_OLAND) || (adev->asic_type == CHIP_HAINAN))
				data |= LS2_EXIT_TIME(5);
			if (orig != data)
				si_pif_phy1_wreg(adev,PB1_PIF_CNTL, data);

			if (!disable_clkreq &&
			    !pci_is_root_bus(adev->pdev->bus)) {
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
				orig = data = RREG32_PCIE_PORT(PCIE_LC_CNTL2);
				data |= LC_ALLOW_PDWN_IN_L1 | LC_ALLOW_PDWN_IN_L23;
				if (orig != data)
					WREG32_PCIE_PORT(PCIE_LC_CNTL2, data);

				orig = data = RREG32(THM_CLK_CNTL);
				data &= ~(CMON_CLK_SEL_MASK | TMON_CLK_SEL_MASK);
				data |= CMON_CLK_SEL(1) | TMON_CLK_SEL(1);
				if (orig != data)
					WREG32(THM_CLK_CNTL, data);

				orig = data = RREG32(MISC_CLK_CNTL);
				data &= ~(DEEP_SLEEP_CLK_SEL_MASK | ZCLK_SEL_MASK);
				data |= DEEP_SLEEP_CLK_SEL(1) | ZCLK_SEL(1);
				if (orig != data)
					WREG32(MISC_CLK_CNTL, data);

				orig = data = RREG32(CG_CLKPIN_CNTL);
				data &= ~BCLK_AS_XCLK;
				if (orig != data)
					WREG32(CG_CLKPIN_CNTL, data);

				orig = data = RREG32(CG_CLKPIN_CNTL_2);
				data &= ~FORCE_BIF_REFCLK_EN;
				if (orig != data)
					WREG32(CG_CLKPIN_CNTL_2, data);

				orig = data = RREG32(MPLL_BYPASSCLK_SEL);
				data &= ~MPLL_CLKOUT_SEL_MASK;
				data |= MPLL_CLKOUT_SEL(4);
				if (orig != data)
					WREG32(MPLL_BYPASSCLK_SEL, data);

				orig = data = RREG32(SPLL_CNTL_MODE);
				data &= ~SPLL_REFCLK_SEL_MASK;
				if (orig != data)
					WREG32(SPLL_CNTL_MODE, data);
			}
		}
	} else {
		if (orig != data)
			WREG32_PCIE_PORT(PCIE_LC_CNTL, data);
	}

	orig = data = RREG32_PCIE(PCIE_CNTL2);
	data |= SLV_MEM_LS_EN | MST_MEM_LS_EN | REPLAY_MEM_LS_EN;
	if (orig != data)
		WREG32_PCIE(PCIE_CNTL2, data);

	if (!disable_l0s) {
		data = RREG32_PCIE_PORT(PCIE_LC_N_FTS_CNTL);
		if((data & LC_N_FTS_MASK) == LC_N_FTS_MASK) {
			data = RREG32_PCIE(PCIE_LC_STATUS1);
			if ((data & LC_REVERSE_XMIT) && (data & LC_REVERSE_RCVR)) {
				orig = data = RREG32_PCIE_PORT(PCIE_LC_CNTL);
				data &= ~LC_L0S_INACTIVITY_MASK;
				if (orig != data)
					WREG32_PCIE_PORT(PCIE_LC_CNTL, data);
			}
		}
	}
}