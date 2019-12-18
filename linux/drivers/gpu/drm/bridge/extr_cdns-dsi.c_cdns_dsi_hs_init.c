#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct cdns_dsi_output {TYPE_1__* dev; int /*<<< orphan*/  phy_opts; } ;
struct cdns_dsi {scalar_t__ regs; int /*<<< orphan*/  dphy; struct cdns_dsi_output output; } ;
struct TYPE_2__ {int /*<<< orphan*/  lanes; } ;

/* Variables and functions */
 int DPHY_ALL_D_PDN ; 
 int DPHY_CMN_PDN ; 
 int DPHY_CMN_PSO ; 
 int DPHY_C_PDN ; 
 int DPHY_C_RSTB ; 
 int DPHY_D_RSTB (int /*<<< orphan*/ ) ; 
 int DPHY_PLL_PDN ; 
 int DPHY_PLL_PSO ; 
 scalar_t__ MCTL_DPHY_CFG0 ; 
 scalar_t__ MCTL_MAIN_STS ; 
 scalar_t__ MCTL_MAIN_STS_CLR ; 
 int /*<<< orphan*/  PHY_MODE_MIPI_DPHY ; 
 int PLL_LOCKED ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_configure (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phy_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_power_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_set_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl_poll_timeout (scalar_t__,int,int,int,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void cdns_dsi_hs_init(struct cdns_dsi *dsi)
{
	struct cdns_dsi_output *output = &dsi->output;
	u32 status;

	/*
	 * Power all internal DPHY blocks down and maintain their reset line
	 * asserted before changing the DPHY config.
	 */
	writel(DPHY_CMN_PSO | DPHY_PLL_PSO | DPHY_ALL_D_PDN | DPHY_C_PDN |
	       DPHY_CMN_PDN | DPHY_PLL_PDN,
	       dsi->regs + MCTL_DPHY_CFG0);

	phy_init(dsi->dphy);
	phy_set_mode(dsi->dphy, PHY_MODE_MIPI_DPHY);
	phy_configure(dsi->dphy, &output->phy_opts);
	phy_power_on(dsi->dphy);

	/* Activate the PLL and wait until it's locked. */
	writel(PLL_LOCKED, dsi->regs + MCTL_MAIN_STS_CLR);
	writel(DPHY_CMN_PSO | DPHY_ALL_D_PDN | DPHY_C_PDN | DPHY_CMN_PDN,
	       dsi->regs + MCTL_DPHY_CFG0);
	WARN_ON_ONCE(readl_poll_timeout(dsi->regs + MCTL_MAIN_STS, status,
					status & PLL_LOCKED, 100, 100));
	/* De-assert data and clock reset lines. */
	writel(DPHY_CMN_PSO | DPHY_ALL_D_PDN | DPHY_C_PDN | DPHY_CMN_PDN |
	       DPHY_D_RSTB(output->dev->lanes) | DPHY_C_RSTB,
	       dsi->regs + MCTL_DPHY_CFG0);
}