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
struct phy {int dummy; } ;
struct cdns_dphy {scalar_t__ regs; int /*<<< orphan*/  pll_ref_clk; int /*<<< orphan*/  psm_clk; } ;

/* Variables and functions */
 scalar_t__ DPHY_CMN_SSM ; 
 int DPHY_CMN_SSM_EN ; 
 int DPHY_CMN_TX_MODE_EN ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 struct cdns_dphy* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int cdns_dphy_power_on(struct phy *phy)
{
	struct cdns_dphy *dphy = phy_get_drvdata(phy);

	clk_prepare_enable(dphy->psm_clk);
	clk_prepare_enable(dphy->pll_ref_clk);

	/* Start TX state machine. */
	writel(DPHY_CMN_SSM_EN | DPHY_CMN_TX_MODE_EN,
	       dphy->regs + DPHY_CMN_SSM);

	return 0;
}