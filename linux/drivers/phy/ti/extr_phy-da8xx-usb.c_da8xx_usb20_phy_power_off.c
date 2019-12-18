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
struct da8xx_usb_phy {int /*<<< orphan*/  usb20_clk; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFGCHIP (int) ; 
 int /*<<< orphan*/  CFGCHIP2_OTGPWRDN ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct da8xx_usb_phy* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  regmap_write_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da8xx_usb20_phy_power_off(struct phy *phy)
{
	struct da8xx_usb_phy *d_phy = phy_get_drvdata(phy);

	regmap_write_bits(d_phy->regmap, CFGCHIP(2), CFGCHIP2_OTGPWRDN,
			  CFGCHIP2_OTGPWRDN);

	clk_disable_unprepare(d_phy->usb20_clk);

	return 0;
}