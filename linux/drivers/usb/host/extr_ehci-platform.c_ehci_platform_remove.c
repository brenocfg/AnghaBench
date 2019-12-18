#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usb_hcd {int dummy; } ;
struct usb_ehci_pdata {int /*<<< orphan*/  (* power_off ) (struct platform_device*) ;} ;
struct TYPE_2__ {int /*<<< orphan*/ * platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct ehci_platform_priv {scalar_t__* clks; int /*<<< orphan*/  rsts; } ;

/* Variables and functions */
 int EHCI_MAX_CLKS ; 
 int /*<<< orphan*/  clk_put (scalar_t__) ; 
 struct usb_ehci_pdata* dev_get_platdata (TYPE_1__*) ; 
 struct usb_ehci_pdata ehci_platform_defaults ; 
 struct ehci_platform_priv* hcd_to_ehci_priv (struct usb_hcd*) ; 
 struct usb_hcd* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct platform_device*) ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_remove_hcd (struct usb_hcd*) ; 

__attribute__((used)) static int ehci_platform_remove(struct platform_device *dev)
{
	struct usb_hcd *hcd = platform_get_drvdata(dev);
	struct usb_ehci_pdata *pdata = dev_get_platdata(&dev->dev);
	struct ehci_platform_priv *priv = hcd_to_ehci_priv(hcd);
	int clk;

	usb_remove_hcd(hcd);

	if (pdata->power_off)
		pdata->power_off(dev);

	reset_control_assert(priv->rsts);

	for (clk = 0; clk < EHCI_MAX_CLKS && priv->clks[clk]; clk++)
		clk_put(priv->clks[clk]);

	usb_put_hcd(hcd);

	if (pdata == &ehci_platform_defaults)
		dev->dev.platform_data = NULL;

	return 0;
}