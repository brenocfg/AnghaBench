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
struct da8xx_usb_phy {int /*<<< orphan*/  regmap; int /*<<< orphan*/  usb11_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFGCHIP (int) ; 
 int /*<<< orphan*/  CFGCHIP2_USB1SUSPENDM ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 struct da8xx_usb_phy* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  regmap_write_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da8xx_usb11_phy_power_on(struct phy *phy)
{
	struct da8xx_usb_phy *d_phy = phy_get_drvdata(phy);
	int ret;

	ret = clk_prepare_enable(d_phy->usb11_clk);
	if (ret)
		return ret;

	regmap_write_bits(d_phy->regmap, CFGCHIP(2), CFGCHIP2_USB1SUSPENDM,
			  CFGCHIP2_USB1SUSPENDM);

	return 0;
}