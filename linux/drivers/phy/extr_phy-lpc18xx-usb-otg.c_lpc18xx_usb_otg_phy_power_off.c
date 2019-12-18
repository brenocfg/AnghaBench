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
struct lpc18xx_usb_otg_phy {int /*<<< orphan*/  clk; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPC18XX_CREG_CREG0 ; 
 int /*<<< orphan*/  LPC18XX_CREG_CREG0_USB0PHY ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 struct lpc18xx_usb_otg_phy* phy_get_drvdata (struct phy*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lpc18xx_usb_otg_phy_power_off(struct phy *phy)
{
	struct lpc18xx_usb_otg_phy *lpc = phy_get_drvdata(phy);
	int ret;

	ret = regmap_update_bits(lpc->reg, LPC18XX_CREG_CREG0,
				 LPC18XX_CREG_CREG0_USB0PHY,
				 LPC18XX_CREG_CREG0_USB0PHY);
	if (ret)
		return ret;

	clk_disable(lpc->clk);

	return 0;
}