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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct mxc_usbh_platform_data {scalar_t__ otg; int /*<<< orphan*/  (* exit ) (struct platform_device*) ;} ;
struct ehci_mxc_priv {scalar_t__ phyclk; scalar_t__ ahbclk; scalar_t__ usbclk; } ;
struct ehci_hcd {scalar_t__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 struct mxc_usbh_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 struct ehci_hcd* hcd_to_ehci (struct usb_hcd*) ; 
 struct usb_hcd* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  stub1 (struct platform_device*) ; 
 int /*<<< orphan*/  usb_phy_shutdown (scalar_t__) ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_remove_hcd (struct usb_hcd*) ; 

__attribute__((used)) static int ehci_mxc_drv_remove(struct platform_device *pdev)
{
	struct mxc_usbh_platform_data *pdata = dev_get_platdata(&pdev->dev);
	struct usb_hcd *hcd = platform_get_drvdata(pdev);
	struct ehci_hcd *ehci = hcd_to_ehci(hcd);
	struct ehci_mxc_priv *priv = (struct ehci_mxc_priv *) ehci->priv;

	usb_remove_hcd(hcd);

	if (pdata && pdata->exit)
		pdata->exit(pdev);

	if (pdata && pdata->otg)
		usb_phy_shutdown(pdata->otg);

	clk_disable_unprepare(priv->usbclk);
	clk_disable_unprepare(priv->ahbclk);

	if (priv->phyclk)
		clk_disable_unprepare(priv->phyclk);

	usb_put_hcd(hcd);
	return 0;
}