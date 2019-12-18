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
struct cdns_dp_phy {scalar_t__ sd_base; } ;

/* Variables and functions */
 scalar_t__ CMN_BGCAL_INIT_TMR ; 
 scalar_t__ CMN_BGCAL_ITER_TMR ; 
 scalar_t__ CMN_IBCAL_INIT_TMR ; 
 scalar_t__ CMN_PDIAG_PLL0_CP_IADJ_M0 ; 
 scalar_t__ CMN_PDIAG_PLL0_CP_PADJ_M0 ; 
 scalar_t__ CMN_PDIAG_PLL0_FILT_PADJ_M0 ; 
 scalar_t__ CMN_PLL0_DSM_DIAG_M0 ; 
 scalar_t__ CMN_PLL0_VCOCAL_INIT_TMR ; 
 scalar_t__ CMN_PLL0_VCOCAL_ITER_TMR ; 
 scalar_t__ CMN_PLL0_VCOCAL_REFTIM_START ; 
 scalar_t__ CMN_PLL1_VCOCAL_INIT_TMR ; 
 scalar_t__ CMN_PLL1_VCOCAL_ITER_TMR ; 
 scalar_t__ CMN_PLLSM0_PLLLOCK_TMR ; 
 scalar_t__ CMN_PLLSM0_PLLPRE_TMR ; 
 scalar_t__ CMN_PLLSM1_PLLLOCK_TMR ; 
 scalar_t__ CMN_PLLSM1_PLLPRE_TMR ; 
 scalar_t__ CMN_RXCAL_INIT_TMR ; 
 scalar_t__ CMN_RXCAL_ITER_TMR ; 
 scalar_t__ CMN_SD_CAL_INIT_TMR ; 
 scalar_t__ CMN_SD_CAL_ITER_TMR ; 
 scalar_t__ CMN_SD_CAL_PLLCNT_START ; 
 scalar_t__ CMN_SD_CAL_REFTIM_START ; 
 scalar_t__ CMN_SSM_BIAS_TMR ; 
 scalar_t__ CMN_TXPDCAL_INIT_TMR ; 
 scalar_t__ CMN_TXPDCAL_ITER_TMR ; 
 scalar_t__ CMN_TXPUCAL_INIT_TMR ; 
 scalar_t__ CMN_TXPUCAL_ITER_TMR ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void cdns_dp_phy_pma_cmn_cfg_25mhz(struct cdns_dp_phy *cdns_phy)
{
	/* refclock registers - assumes 25 MHz refclock */
	writel(0x0019, cdns_phy->sd_base + CMN_SSM_BIAS_TMR);
	writel(0x0032, cdns_phy->sd_base + CMN_PLLSM0_PLLPRE_TMR);
	writel(0x00D1, cdns_phy->sd_base + CMN_PLLSM0_PLLLOCK_TMR);
	writel(0x0032, cdns_phy->sd_base + CMN_PLLSM1_PLLPRE_TMR);
	writel(0x00D1, cdns_phy->sd_base + CMN_PLLSM1_PLLLOCK_TMR);
	writel(0x007D, cdns_phy->sd_base + CMN_BGCAL_INIT_TMR);
	writel(0x007D, cdns_phy->sd_base + CMN_BGCAL_ITER_TMR);
	writel(0x0019, cdns_phy->sd_base + CMN_IBCAL_INIT_TMR);
	writel(0x001E, cdns_phy->sd_base + CMN_TXPUCAL_INIT_TMR);
	writel(0x0006, cdns_phy->sd_base + CMN_TXPUCAL_ITER_TMR);
	writel(0x001E, cdns_phy->sd_base + CMN_TXPDCAL_INIT_TMR);
	writel(0x0006, cdns_phy->sd_base + CMN_TXPDCAL_ITER_TMR);
	writel(0x02EE, cdns_phy->sd_base + CMN_RXCAL_INIT_TMR);
	writel(0x0006, cdns_phy->sd_base + CMN_RXCAL_ITER_TMR);
	writel(0x0002, cdns_phy->sd_base + CMN_SD_CAL_INIT_TMR);
	writel(0x0002, cdns_phy->sd_base + CMN_SD_CAL_ITER_TMR);
	writel(0x000E, cdns_phy->sd_base + CMN_SD_CAL_REFTIM_START);
	writel(0x012B, cdns_phy->sd_base + CMN_SD_CAL_PLLCNT_START);
	/* PLL registers */
	writel(0x0409, cdns_phy->sd_base + CMN_PDIAG_PLL0_CP_PADJ_M0);
	writel(0x1001, cdns_phy->sd_base + CMN_PDIAG_PLL0_CP_IADJ_M0);
	writel(0x0F08, cdns_phy->sd_base + CMN_PDIAG_PLL0_FILT_PADJ_M0);
	writel(0x0004, cdns_phy->sd_base + CMN_PLL0_DSM_DIAG_M0);
	writel(0x00FA, cdns_phy->sd_base + CMN_PLL0_VCOCAL_INIT_TMR);
	writel(0x0004, cdns_phy->sd_base + CMN_PLL0_VCOCAL_ITER_TMR);
	writel(0x00FA, cdns_phy->sd_base + CMN_PLL1_VCOCAL_INIT_TMR);
	writel(0x0004, cdns_phy->sd_base + CMN_PLL1_VCOCAL_ITER_TMR);
	writel(0x0318, cdns_phy->sd_base + CMN_PLL0_VCOCAL_REFTIM_START);
}