#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct cdns_dsi {scalar_t__ regs; TYPE_1__* dphy; } ;
struct cdns_dphy_cfg {int /*<<< orphan*/  nlanes; } ;
struct TYPE_4__ {scalar_t__ regs; } ;

/* Variables and functions */
 int DPHY_ALL_D_PDN ; 
 int /*<<< orphan*/  DPHY_CLK_CFG_LEFT_DRIVES_LEFT ; 
 int DPHY_CMN_PDN ; 
 int DPHY_CMN_PSO ; 
 scalar_t__ DPHY_CMN_SSM ; 
 int DPHY_CMN_SSM_EN ; 
 int DPHY_CMN_TX_MODE_EN ; 
 int DPHY_C_PDN ; 
 int DPHY_C_RSTB ; 
 int DPHY_D_RSTB (int /*<<< orphan*/ ) ; 
 int DPHY_PLL_PDN ; 
 int DPHY_PLL_PSO ; 
 scalar_t__ MCTL_DPHY_CFG0 ; 
 scalar_t__ MCTL_MAIN_STS ; 
 scalar_t__ MCTL_MAIN_STS_CLR ; 
 int PLL_LOCKED ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdns_dphy_set_clk_lane_cfg (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdns_dphy_set_pll_cfg (TYPE_1__*,struct cdns_dphy_cfg const*) ; 
 int /*<<< orphan*/  cdns_dphy_setup_psm (TYPE_1__*) ; 
 int /*<<< orphan*/  readl_poll_timeout (scalar_t__,int,int,int,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void cdns_dsi_hs_init(struct cdns_dsi *dsi,
			     const struct cdns_dphy_cfg *dphy_cfg)
{
	u32 status;

	/*
	 * Power all internal DPHY blocks down and maintain their reset line
	 * asserted before changing the DPHY config.
	 */
	writel(DPHY_CMN_PSO | DPHY_PLL_PSO | DPHY_ALL_D_PDN | DPHY_C_PDN |
	       DPHY_CMN_PDN | DPHY_PLL_PDN,
	       dsi->regs + MCTL_DPHY_CFG0);

	/*
	 * Configure the internal PSM clk divider so that the DPHY has a
	 * 1MHz clk (or something close).
	 */
	WARN_ON_ONCE(cdns_dphy_setup_psm(dsi->dphy));

	/*
	 * Configure attach clk lanes to data lanes: the DPHY has 2 clk lanes
	 * and 8 data lanes, each clk lane can be attache different set of
	 * data lanes. The 2 groups are named 'left' and 'right', so here we
	 * just say that we want the 'left' clk lane to drive the 'left' data
	 * lanes.
	 */
	cdns_dphy_set_clk_lane_cfg(dsi->dphy, DPHY_CLK_CFG_LEFT_DRIVES_LEFT);

	/*
	 * Configure the DPHY PLL that will be used to generate the TX byte
	 * clk.
	 */
	cdns_dphy_set_pll_cfg(dsi->dphy, dphy_cfg);

	/* Start TX state machine. */
	writel(DPHY_CMN_SSM_EN | DPHY_CMN_TX_MODE_EN,
	       dsi->dphy->regs + DPHY_CMN_SSM);

	/* Activate the PLL and wait until it's locked. */
	writel(PLL_LOCKED, dsi->regs + MCTL_MAIN_STS_CLR);
	writel(DPHY_CMN_PSO | DPHY_ALL_D_PDN | DPHY_C_PDN | DPHY_CMN_PDN,
	       dsi->regs + MCTL_DPHY_CFG0);
	WARN_ON_ONCE(readl_poll_timeout(dsi->regs + MCTL_MAIN_STS, status,
					status & PLL_LOCKED, 100, 100));
	/* De-assert data and clock reset lines. */
	writel(DPHY_CMN_PSO | DPHY_ALL_D_PDN | DPHY_C_PDN | DPHY_CMN_PDN |
	       DPHY_D_RSTB(dphy_cfg->nlanes) | DPHY_C_RSTB,
	       dsi->regs + MCTL_DPHY_CFG0);
}