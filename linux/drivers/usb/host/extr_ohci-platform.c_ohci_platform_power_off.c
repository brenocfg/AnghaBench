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
struct platform_device {int dummy; } ;
struct ohci_platform_priv {scalar_t__* clks; } ;

/* Variables and functions */
 int OHCI_MAX_CLKS ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 struct ohci_platform_priv* hcd_to_ohci_priv (struct usb_hcd*) ; 
 struct usb_hcd* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static void ohci_platform_power_off(struct platform_device *dev)
{
	struct usb_hcd *hcd = platform_get_drvdata(dev);
	struct ohci_platform_priv *priv = hcd_to_ohci_priv(hcd);
	int clk;

	for (clk = OHCI_MAX_CLKS - 1; clk >= 0; clk--)
		if (priv->clks[clk])
			clk_disable_unprepare(priv->clks[clk]);
}