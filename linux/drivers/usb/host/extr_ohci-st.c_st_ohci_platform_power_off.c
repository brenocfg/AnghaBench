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
struct usb_hcd {int dummy; } ;
struct st_ohci_platform_priv {scalar_t__* clks; int /*<<< orphan*/  phy; int /*<<< orphan*/  rst; int /*<<< orphan*/  pwr; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int USB_MAX_CLKS ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 struct st_ohci_platform_priv* hcd_to_ohci_priv (struct usb_hcd*) ; 
 int /*<<< orphan*/  phy_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_power_off (int /*<<< orphan*/ ) ; 
 struct usb_hcd* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void st_ohci_platform_power_off(struct platform_device *dev)
{
	struct usb_hcd *hcd = platform_get_drvdata(dev);
	struct st_ohci_platform_priv *priv = hcd_to_ohci_priv(hcd);

	int clk;

	reset_control_assert(priv->pwr);

	reset_control_assert(priv->rst);

	phy_power_off(priv->phy);

	phy_exit(priv->phy);

	for (clk = USB_MAX_CLKS - 1; clk >= 0; clk--)
		if (priv->clks[clk])
			clk_disable_unprepare(priv->clks[clk]);
}