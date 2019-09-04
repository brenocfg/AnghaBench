#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct regmap {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  clk; } ;
struct da8xx_usb1_clk48 {TYPE_1__ hw; } ;
struct da8xx_usb0_clk48 {TYPE_1__ hw; } ;
struct clk_hw {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct da8xx_usb1_clk48*) ; 
 int PTR_ERR (struct da8xx_usb1_clk48*) ; 
 struct clk_hw* clk_hw_get_parent_by_index (TYPE_1__*,int) ; 
 int /*<<< orphan*/  clk_hw_register_clkdev (TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/  clk_set_parent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct da8xx_usb1_clk48* da8xx_cfgchip_register_usb0_clk48 (struct device*,struct regmap*) ; 
 struct da8xx_usb1_clk48* da8xx_cfgchip_register_usb1_clk48 (struct device*,struct regmap*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 

__attribute__((used)) static int da8xx_cfgchip_register_usb_phy_clk(struct device *dev,
					      struct regmap *regmap)
{
	struct da8xx_usb0_clk48 *usb0;
	struct da8xx_usb1_clk48 *usb1;
	struct clk_hw *parent;

	usb0 = da8xx_cfgchip_register_usb0_clk48(dev, regmap);
	if (IS_ERR(usb0))
		return PTR_ERR(usb0);

	/*
	 * All existing boards use pll0_auxclk as the parent and new boards
	 * should use device tree, so hard-coding the value (1) here.
	 */
	parent = clk_hw_get_parent_by_index(&usb0->hw, 1);
	if (parent)
		clk_set_parent(usb0->hw.clk, parent->clk);
	else
		dev_warn(dev, "Failed to find usb0 parent clock\n");

	usb1 = da8xx_cfgchip_register_usb1_clk48(dev, regmap);
	if (IS_ERR(usb1))
		return PTR_ERR(usb1);

	/*
	 * All existing boards use usb0_clk48 as the parent and new boards
	 * should use device tree, so hard-coding the value (0) here.
	 */
	parent = clk_hw_get_parent_by_index(&usb1->hw, 0);
	if (parent)
		clk_set_parent(usb1->hw.clk, parent->clk);
	else
		dev_warn(dev, "Failed to find usb1 parent clock\n");

	clk_hw_register_clkdev(&usb0->hw, "usb0_clk48", "da8xx-usb-phy");
	clk_hw_register_clkdev(&usb1->hw, "usb1_clk48", "da8xx-usb-phy");

	return 0;
}