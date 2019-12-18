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
struct sunxi_priv_data {scalar_t__ interface; int clk_enabled; int /*<<< orphan*/  tx_clk; scalar_t__ regulator; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ PHY_INTERFACE_MODE_RGMII ; 
 int /*<<< orphan*/  SUN7I_GMAC_GMII_RGMII_RATE ; 
 int /*<<< orphan*/  SUN7I_GMAC_MII_RATE ; 
 int clk_prepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_enable (scalar_t__) ; 

__attribute__((used)) static int sun7i_gmac_init(struct platform_device *pdev, void *priv)
{
	struct sunxi_priv_data *gmac = priv;
	int ret;

	if (gmac->regulator) {
		ret = regulator_enable(gmac->regulator);
		if (ret)
			return ret;
	}

	/* Set GMAC interface port mode
	 *
	 * The GMAC TX clock lines are configured by setting the clock
	 * rate, which then uses the auto-reparenting feature of the
	 * clock driver, and enabling/disabling the clock.
	 */
	if (gmac->interface == PHY_INTERFACE_MODE_RGMII) {
		clk_set_rate(gmac->tx_clk, SUN7I_GMAC_GMII_RGMII_RATE);
		clk_prepare_enable(gmac->tx_clk);
		gmac->clk_enabled = 1;
	} else {
		clk_set_rate(gmac->tx_clk, SUN7I_GMAC_MII_RATE);
		ret = clk_prepare(gmac->tx_clk);
		if (ret)
			return ret;
	}

	return 0;
}