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
struct sunxi_priv_data {scalar_t__ interface; int clk_enabled; int /*<<< orphan*/  tx_clk; } ;

/* Variables and functions */
 scalar_t__ PHY_INTERFACE_MODE_GMII ; 
 int /*<<< orphan*/  SUN7I_GMAC_GMII_RGMII_RATE ; 
 int /*<<< orphan*/  SUN7I_GMAC_MII_RATE ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sun7i_fix_speed(void *priv, unsigned int speed)
{
	struct sunxi_priv_data *gmac = priv;

	/* only GMII mode requires us to reconfigure the clock lines */
	if (gmac->interface != PHY_INTERFACE_MODE_GMII)
		return;

	if (gmac->clk_enabled) {
		clk_disable(gmac->tx_clk);
		gmac->clk_enabled = 0;
	}
	clk_unprepare(gmac->tx_clk);

	if (speed == 1000) {
		clk_set_rate(gmac->tx_clk, SUN7I_GMAC_GMII_RGMII_RATE);
		clk_prepare_enable(gmac->tx_clk);
		gmac->clk_enabled = 1;
	} else {
		clk_set_rate(gmac->tx_clk, SUN7I_GMAC_MII_RATE);
		clk_prepare(gmac->tx_clk);
	}
}