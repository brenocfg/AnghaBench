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
struct cdns_dp_phy {int max_bit_rate; scalar_t__ sd_base; } ;

/* Variables and functions */
 scalar_t__ CMN_PDIAG_PLL0_CTRL_M0 ; 
 scalar_t__ CMN_PLL0_FRACDIVH_M0 ; 
 scalar_t__ CMN_PLL0_FRACDIVL_M0 ; 
 scalar_t__ CMN_PLL0_HIGH_THR_M0 ; 
 scalar_t__ CMN_PLL0_INTDIV_M0 ; 
 scalar_t__ CMN_PLL0_VCOCAL_PLLCNT_START ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void cdns_dp_phy_pma_cmn_vco_cfg_25mhz(struct cdns_dp_phy *cdns_phy)
{
	/* Assumes 25 MHz refclock */
	switch (cdns_phy->max_bit_rate) {
		/* Setting VCO for 10.8GHz */
	case 2700:
	case 5400:
		writel(0x01B0, cdns_phy->sd_base + CMN_PLL0_INTDIV_M0);
		writel(0x0000, cdns_phy->sd_base + CMN_PLL0_FRACDIVL_M0);
		writel(0x0002, cdns_phy->sd_base + CMN_PLL0_FRACDIVH_M0);
		writel(0x0120, cdns_phy->sd_base + CMN_PLL0_HIGH_THR_M0);
		break;
		/* Setting VCO for 9.72GHz */
	case 2430:
	case 3240:
		writel(0x0184, cdns_phy->sd_base + CMN_PLL0_INTDIV_M0);
		writel(0xCCCD, cdns_phy->sd_base + CMN_PLL0_FRACDIVL_M0);
		writel(0x0002, cdns_phy->sd_base + CMN_PLL0_FRACDIVH_M0);
		writel(0x0104, cdns_phy->sd_base + CMN_PLL0_HIGH_THR_M0);
		break;
		/* Setting VCO for 8.64GHz */
	case 2160:
	case 4320:
		writel(0x0159, cdns_phy->sd_base + CMN_PLL0_INTDIV_M0);
		writel(0x999A, cdns_phy->sd_base + CMN_PLL0_FRACDIVL_M0);
		writel(0x0002, cdns_phy->sd_base + CMN_PLL0_FRACDIVH_M0);
		writel(0x00E7, cdns_phy->sd_base + CMN_PLL0_HIGH_THR_M0);
		break;
		/* Setting VCO for 8.1GHz */
	case 8100:
		writel(0x0144, cdns_phy->sd_base + CMN_PLL0_INTDIV_M0);
		writel(0x0000, cdns_phy->sd_base + CMN_PLL0_FRACDIVL_M0);
		writel(0x0002, cdns_phy->sd_base + CMN_PLL0_FRACDIVH_M0);
		writel(0x00D8, cdns_phy->sd_base + CMN_PLL0_HIGH_THR_M0);
		break;
	}

	writel(0x0002, cdns_phy->sd_base + CMN_PDIAG_PLL0_CTRL_M0);
	writel(0x0318, cdns_phy->sd_base + CMN_PLL0_VCOCAL_PLLCNT_START);
}