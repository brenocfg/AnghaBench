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
struct g12a_mdio_mux {int pll_is_enabled; int /*<<< orphan*/  pll; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ ETH_PHY_CNTL2 ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int g12a_enable_external_mdio(struct g12a_mdio_mux *priv)
{
	/* Reset the mdio bus mux */
	writel_relaxed(0x0, priv->regs + ETH_PHY_CNTL2);

	/* Disable the phy clock if enabled */
	if (priv->pll_is_enabled) {
		clk_disable_unprepare(priv->pll);
		priv->pll_is_enabled = false;
	}

	return 0;
}