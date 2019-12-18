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
struct ralink_usb_phy {int /*<<< orphan*/  rsthost; int /*<<< orphan*/  rstdev; int /*<<< orphan*/  clk; int /*<<< orphan*/  sysctl; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT_SYSC_REG_CLKCFG1 ; 
 struct ralink_usb_phy* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ralink_usb_phy_power_off(struct phy *_phy)
{
	struct ralink_usb_phy *phy = phy_get_drvdata(_phy);

	/* disable the phy */
	regmap_update_bits(phy->sysctl, RT_SYSC_REG_CLKCFG1,
			   phy->clk, 0);

	/* assert the reset lines */
	reset_control_assert(phy->rstdev);
	reset_control_assert(phy->rsthost);

	return 0;
}