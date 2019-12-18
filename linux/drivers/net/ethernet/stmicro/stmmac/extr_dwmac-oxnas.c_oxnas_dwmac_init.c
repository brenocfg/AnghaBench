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
struct platform_device {int dummy; } ;
struct oxnas_dwmac {int /*<<< orphan*/  regmap; int /*<<< orphan*/  clk; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWMAC_AUTO_TX_SOURCE ; 
 int /*<<< orphan*/  DWMAC_CKEN_GTX ; 
 int /*<<< orphan*/  DWMAC_CKEN_RXN_OUT ; 
 int /*<<< orphan*/  DWMAC_CKEN_RX_IN ; 
 int /*<<< orphan*/  DWMAC_CKEN_RX_OUT ; 
 int /*<<< orphan*/  DWMAC_CKEN_TXN_OUT ; 
 int /*<<< orphan*/  DWMAC_CKEN_TX_IN ; 
 int /*<<< orphan*/  DWMAC_CKEN_TX_OUT ; 
 unsigned int DWMAC_RXN_VARDELAY (int) ; 
 unsigned int DWMAC_RX_VARDELAY (int) ; 
 int /*<<< orphan*/  DWMAC_SIMPLE_MUX ; 
 unsigned int DWMAC_TXN_VARDELAY (int) ; 
 unsigned int DWMAC_TX_VARDELAY (int) ; 
 int /*<<< orphan*/  OXNAS_DWMAC_CTRL_REGOFFSET ; 
 int /*<<< orphan*/  OXNAS_DWMAC_DELAY_REGOFFSET ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int device_reset (int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int oxnas_dwmac_init(struct platform_device *pdev, void *priv)
{
	struct oxnas_dwmac *dwmac = priv;
	unsigned int value;
	int ret;

	/* Reset HW here before changing the glue configuration */
	ret = device_reset(dwmac->dev);
	if (ret)
		return ret;

	ret = clk_prepare_enable(dwmac->clk);
	if (ret)
		return ret;

	ret = regmap_read(dwmac->regmap, OXNAS_DWMAC_CTRL_REGOFFSET, &value);
	if (ret < 0) {
		clk_disable_unprepare(dwmac->clk);
		return ret;
	}

	/* Enable GMII_GTXCLK to follow GMII_REFCLK, required for gigabit PHY */
	value |= BIT(DWMAC_CKEN_GTX)		|
		 /* Use simple mux for 25/125 Mhz clock switching */
		 BIT(DWMAC_SIMPLE_MUX)		|
		 /* set auto switch tx clock source */
		 BIT(DWMAC_AUTO_TX_SOURCE)	|
		 /* enable tx & rx vardelay */
		 BIT(DWMAC_CKEN_TX_OUT)		|
		 BIT(DWMAC_CKEN_TXN_OUT)	|
		 BIT(DWMAC_CKEN_TX_IN)		|
		 BIT(DWMAC_CKEN_RX_OUT)		|
		 BIT(DWMAC_CKEN_RXN_OUT)	|
		 BIT(DWMAC_CKEN_RX_IN);
	regmap_write(dwmac->regmap, OXNAS_DWMAC_CTRL_REGOFFSET, value);

	/* set tx & rx vardelay */
	value = DWMAC_TX_VARDELAY(4)	|
		DWMAC_TXN_VARDELAY(2)	|
		DWMAC_RX_VARDELAY(10)	|
		DWMAC_RXN_VARDELAY(8);
	regmap_write(dwmac->regmap, OXNAS_DWMAC_DELAY_REGOFFSET, value);

	return 0;
}