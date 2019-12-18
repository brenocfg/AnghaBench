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
struct rockchip_usb_phy {int /*<<< orphan*/  clk480m; scalar_t__ uart_enabled; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct rockchip_usb_phy* phy_get_drvdata (struct phy*) ; 

__attribute__((used)) static int rockchip_usb_phy_power_off(struct phy *_phy)
{
	struct rockchip_usb_phy *phy = phy_get_drvdata(_phy);

	if (phy->uart_enabled)
		return -EBUSY;

	clk_disable_unprepare(phy->clk480m);

	return 0;
}