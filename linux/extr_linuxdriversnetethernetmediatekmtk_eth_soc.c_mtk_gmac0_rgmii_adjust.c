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
struct mtk_eth {int /*<<< orphan*/  dev; int /*<<< orphan*/ * clks; int /*<<< orphan*/  ethsys; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHSYS_CLKCFG0 ; 
 int /*<<< orphan*/  ETHSYS_TRGMII_CLK_SEL362_5 ; 
 int /*<<< orphan*/  INTF_MODE ; 
 int INTF_MODE_RGMII_1000 ; 
 int INTF_MODE_RGMII_10_100 ; 
 size_t MTK_CLK_TRGPLL ; 
 int RCK_CTRL_RGMII_1000 ; 
 int RCK_CTRL_RGMII_10_100 ; 
 int SPEED_1000 ; 
 int TCK_CTRL_RGMII_1000 ; 
 int TCK_CTRL_RGMII_10_100 ; 
 int /*<<< orphan*/  TRGMII_RCK_CTRL ; 
 int /*<<< orphan*/  TRGMII_TCK_CTRL ; 
 int clk_set_rate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mtk_w32 (struct mtk_eth*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_gmac0_rgmii_adjust(struct mtk_eth *eth, int speed)
{
	u32 val;
	int ret;

	val = (speed == SPEED_1000) ?
		INTF_MODE_RGMII_1000 : INTF_MODE_RGMII_10_100;
	mtk_w32(eth, val, INTF_MODE);

	regmap_update_bits(eth->ethsys, ETHSYS_CLKCFG0,
			   ETHSYS_TRGMII_CLK_SEL362_5,
			   ETHSYS_TRGMII_CLK_SEL362_5);

	val = (speed == SPEED_1000) ? 250000000 : 500000000;
	ret = clk_set_rate(eth->clks[MTK_CLK_TRGPLL], val);
	if (ret)
		dev_err(eth->dev, "Failed to set trgmii pll: %d\n", ret);

	val = (speed == SPEED_1000) ?
		RCK_CTRL_RGMII_1000 : RCK_CTRL_RGMII_10_100;
	mtk_w32(eth, val, TRGMII_RCK_CTRL);

	val = (speed == SPEED_1000) ?
		TCK_CTRL_RGMII_1000 : TCK_CTRL_RGMII_10_100;
	mtk_w32(eth, val, TRGMII_TCK_CTRL);
}