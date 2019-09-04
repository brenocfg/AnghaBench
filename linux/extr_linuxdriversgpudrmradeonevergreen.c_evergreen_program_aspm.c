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
struct radeon_device {int flags; int family; } ;

/* Variables and functions */
#define  CHIP_ARUBA 136 
 int CHIP_BARTS ; 
#define  CHIP_CEDAR 135 
#define  CHIP_CYPRESS 134 
#define  CHIP_HEMLOCK 133 
#define  CHIP_JUNIPER 132 
#define  CHIP_PALM 131 
#define  CHIP_REDWOOD 130 
#define  CHIP_SUMO 129 
#define  CHIP_SUMO2 128 
 int LC_DYN_LANES_PWR_STATE (int) ; 
 int LC_DYN_LANES_PWR_STATE_MASK ; 
 int LC_L0S_INACTIVITY (int) ; 
 int LC_L0S_INACTIVITY_MASK ; 
 int LC_L1_INACTIVITY (int) ; 
 int LC_L1_INACTIVITY_MASK ; 
 int LC_PMI_TO_L1_DIS ; 
 int LS2_EXIT_TIME (int) ; 
 int LS2_EXIT_TIME_MASK ; 
 int MULTI_PIF ; 
 int /*<<< orphan*/  PB0_PIF_CNTL ; 
 int /*<<< orphan*/  PB0_PIF_PAIRING ; 
 int /*<<< orphan*/  PB0_PIF_PWRDOWN_0 ; 
 int /*<<< orphan*/  PB0_PIF_PWRDOWN_1 ; 
 int /*<<< orphan*/  PB1_PIF_CNTL ; 
 int /*<<< orphan*/  PB1_PIF_PAIRING ; 
 int /*<<< orphan*/  PB1_PIF_PWRDOWN_0 ; 
 int /*<<< orphan*/  PB1_PIF_PWRDOWN_1 ; 
 int /*<<< orphan*/  PCIE_LC_CNTL ; 
 int /*<<< orphan*/  PCIE_LC_LINK_WIDTH_CNTL ; 
 int PLL_POWER_STATE_IN_OFF_0 (int) ; 
 int PLL_POWER_STATE_IN_OFF_0_MASK ; 
 int PLL_POWER_STATE_IN_OFF_1 (int) ; 
 int PLL_POWER_STATE_IN_OFF_1_MASK ; 
 int PLL_POWER_STATE_IN_TXS2_0 (int) ; 
 int PLL_POWER_STATE_IN_TXS2_0_MASK ; 
 int PLL_POWER_STATE_IN_TXS2_1 (int) ; 
 int PLL_POWER_STATE_IN_TXS2_1_MASK ; 
 int PLL_RAMP_UP_TIME_0 (int) ; 
 int PLL_RAMP_UP_TIME_0_MASK ; 
 int PLL_RAMP_UP_TIME_1 (int) ; 
 int PLL_RAMP_UP_TIME_1_MASK ; 
 int RADEON_IS_IGP ; 
 int RADEON_IS_PCIE ; 
 int RREG32_PCIE_PORT (int /*<<< orphan*/ ) ; 
 int RREG32_PIF_PHY0 (int /*<<< orphan*/ ) ; 
 int RREG32_PIF_PHY1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_PCIE_PORT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_PIF_PHY0 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_PIF_PHY1 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ radeon_aspm ; 

void evergreen_program_aspm(struct radeon_device *rdev)
{
	u32 data, orig;
	u32 pcie_lc_cntl, pcie_lc_cntl_old;
	bool disable_l0s, disable_l1 = false, disable_plloff_in_l1 = false;
	/* fusion_platform = true
	 * if the system is a fusion system
	 * (APU or DGPU in a fusion system).
	 * todo: check if the system is a fusion platform.
	 */
	bool fusion_platform = false;

	if (radeon_aspm == 0)
		return;

	if (!(rdev->flags & RADEON_IS_PCIE))
		return;

	switch (rdev->family) {
	case CHIP_CYPRESS:
	case CHIP_HEMLOCK:
	case CHIP_JUNIPER:
	case CHIP_REDWOOD:
	case CHIP_CEDAR:
	case CHIP_SUMO:
	case CHIP_SUMO2:
	case CHIP_PALM:
	case CHIP_ARUBA:
		disable_l0s = true;
		break;
	default:
		disable_l0s = false;
		break;
	}

	if (rdev->flags & RADEON_IS_IGP)
		fusion_platform = true; /* XXX also dGPUs in a fusion system */

	data = orig = RREG32_PIF_PHY0(PB0_PIF_PAIRING);
	if (fusion_platform)
		data &= ~MULTI_PIF;
	else
		data |= MULTI_PIF;
	if (data != orig)
		WREG32_PIF_PHY0(PB0_PIF_PAIRING, data);

	data = orig = RREG32_PIF_PHY1(PB1_PIF_PAIRING);
	if (fusion_platform)
		data &= ~MULTI_PIF;
	else
		data |= MULTI_PIF;
	if (data != orig)
		WREG32_PIF_PHY1(PB1_PIF_PAIRING, data);

	pcie_lc_cntl = pcie_lc_cntl_old = RREG32_PCIE_PORT(PCIE_LC_CNTL);
	pcie_lc_cntl &= ~(LC_L0S_INACTIVITY_MASK | LC_L1_INACTIVITY_MASK);
	if (!disable_l0s) {
		if (rdev->family >= CHIP_BARTS)
			pcie_lc_cntl |= LC_L0S_INACTIVITY(7);
		else
			pcie_lc_cntl |= LC_L0S_INACTIVITY(3);
	}

	if (!disable_l1) {
		if (rdev->family >= CHIP_BARTS)
			pcie_lc_cntl |= LC_L1_INACTIVITY(7);
		else
			pcie_lc_cntl |= LC_L1_INACTIVITY(8);

		if (!disable_plloff_in_l1) {
			data = orig = RREG32_PIF_PHY0(PB0_PIF_PWRDOWN_0);
			data &= ~(PLL_POWER_STATE_IN_OFF_0_MASK | PLL_POWER_STATE_IN_TXS2_0_MASK);
			data |= PLL_POWER_STATE_IN_OFF_0(7) | PLL_POWER_STATE_IN_TXS2_0(7);
			if (data != orig)
				WREG32_PIF_PHY0(PB0_PIF_PWRDOWN_0, data);

			data = orig = RREG32_PIF_PHY0(PB0_PIF_PWRDOWN_1);
			data &= ~(PLL_POWER_STATE_IN_OFF_1_MASK | PLL_POWER_STATE_IN_TXS2_1_MASK);
			data |= PLL_POWER_STATE_IN_OFF_1(7) | PLL_POWER_STATE_IN_TXS2_1(7);
			if (data != orig)
				WREG32_PIF_PHY0(PB0_PIF_PWRDOWN_1, data);

			data = orig = RREG32_PIF_PHY1(PB1_PIF_PWRDOWN_0);
			data &= ~(PLL_POWER_STATE_IN_OFF_0_MASK | PLL_POWER_STATE_IN_TXS2_0_MASK);
			data |= PLL_POWER_STATE_IN_OFF_0(7) | PLL_POWER_STATE_IN_TXS2_0(7);
			if (data != orig)
				WREG32_PIF_PHY1(PB1_PIF_PWRDOWN_0, data);

			data = orig = RREG32_PIF_PHY1(PB1_PIF_PWRDOWN_1);
			data &= ~(PLL_POWER_STATE_IN_OFF_1_MASK | PLL_POWER_STATE_IN_TXS2_1_MASK);
			data |= PLL_POWER_STATE_IN_OFF_1(7) | PLL_POWER_STATE_IN_TXS2_1(7);
			if (data != orig)
				WREG32_PIF_PHY1(PB1_PIF_PWRDOWN_1, data);

			if (rdev->family >= CHIP_BARTS) {
				data = orig = RREG32_PIF_PHY0(PB0_PIF_PWRDOWN_0);
				data &= ~PLL_RAMP_UP_TIME_0_MASK;
				data |= PLL_RAMP_UP_TIME_0(4);
				if (data != orig)
					WREG32_PIF_PHY0(PB0_PIF_PWRDOWN_0, data);

				data = orig = RREG32_PIF_PHY0(PB0_PIF_PWRDOWN_1);
				data &= ~PLL_RAMP_UP_TIME_1_MASK;
				data |= PLL_RAMP_UP_TIME_1(4);
				if (data != orig)
					WREG32_PIF_PHY0(PB0_PIF_PWRDOWN_1, data);

				data = orig = RREG32_PIF_PHY1(PB1_PIF_PWRDOWN_0);
				data &= ~PLL_RAMP_UP_TIME_0_MASK;
				data |= PLL_RAMP_UP_TIME_0(4);
				if (data != orig)
					WREG32_PIF_PHY1(PB1_PIF_PWRDOWN_0, data);

				data = orig = RREG32_PIF_PHY1(PB1_PIF_PWRDOWN_1);
				data &= ~PLL_RAMP_UP_TIME_1_MASK;
				data |= PLL_RAMP_UP_TIME_1(4);
				if (data != orig)
					WREG32_PIF_PHY1(PB1_PIF_PWRDOWN_1, data);
			}

			data = orig = RREG32_PCIE_PORT(PCIE_LC_LINK_WIDTH_CNTL);
			data &= ~LC_DYN_LANES_PWR_STATE_MASK;
			data |= LC_DYN_LANES_PWR_STATE(3);
			if (data != orig)
				WREG32_PCIE_PORT(PCIE_LC_LINK_WIDTH_CNTL, data);

			if (rdev->family >= CHIP_BARTS) {
				data = orig = RREG32_PIF_PHY0(PB0_PIF_CNTL);
				data &= ~LS2_EXIT_TIME_MASK;
				data |= LS2_EXIT_TIME(1);
				if (data != orig)
					WREG32_PIF_PHY0(PB0_PIF_CNTL, data);

				data = orig = RREG32_PIF_PHY1(PB1_PIF_CNTL);
				data &= ~LS2_EXIT_TIME_MASK;
				data |= LS2_EXIT_TIME(1);
				if (data != orig)
					WREG32_PIF_PHY1(PB1_PIF_CNTL, data);
			}
		}
	}

	/* evergreen parts only */
	if (rdev->family < CHIP_BARTS)
		pcie_lc_cntl |= LC_PMI_TO_L1_DIS;

	if (pcie_lc_cntl != pcie_lc_cntl_old)
		WREG32_PCIE_PORT(PCIE_LC_CNTL, pcie_lc_cntl);
}