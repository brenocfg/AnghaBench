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
struct unimac_mdio_priv {int clk_freq; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_CFG ; 
 int MDIO_CLK_DIV_MASK ; 
 int MDIO_CLK_DIV_SHIFT ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int unimac_mdio_readl (struct unimac_mdio_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unimac_mdio_writel (struct unimac_mdio_priv*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void unimac_mdio_clk_set(struct unimac_mdio_priv *priv)
{
	unsigned long rate;
	u32 reg, div;

	/* Keep the hardware default values */
	if (!priv->clk_freq)
		return;

	if (!priv->clk)
		rate = 250000000;
	else
		rate = clk_get_rate(priv->clk);

	div = (rate / (2 * priv->clk_freq)) - 1;
	if (div & ~MDIO_CLK_DIV_MASK) {
		pr_warn("Incorrect MDIO clock frequency, ignoring\n");
		return;
	}

	/* The MDIO clock is the reference clock (typicaly 250Mhz) divided by
	 * 2 x (MDIO_CLK_DIV + 1)
	 */
	reg = unimac_mdio_readl(priv, MDIO_CFG);
	reg &= ~(MDIO_CLK_DIV_MASK << MDIO_CLK_DIV_SHIFT);
	reg |= div << MDIO_CLK_DIV_SHIFT;
	unimac_mdio_writel(priv, reg, MDIO_CFG);
}