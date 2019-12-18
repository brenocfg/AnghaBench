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
struct usb_hcd {scalar_t__ rh_registered; } ;
struct platform_device {int dummy; } ;
struct ehci_hcd_mv {scalar_t__ mode; int /*<<< orphan*/  (* set_vbus ) (int /*<<< orphan*/ ) ;TYPE_1__* otg; } ;
struct TYPE_2__ {int /*<<< orphan*/  otg; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (TYPE_1__*) ; 
 scalar_t__ MV_USB_MODE_HOST ; 
 struct ehci_hcd_mv* hcd_to_ehci_hcd_mv (struct usb_hcd*) ; 
 int /*<<< orphan*/  mv_ehci_disable (struct ehci_hcd_mv*) ; 
 int /*<<< orphan*/  otg_set_host (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct usb_hcd* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_remove_hcd (struct usb_hcd*) ; 

__attribute__((used)) static int mv_ehci_remove(struct platform_device *pdev)
{
	struct usb_hcd *hcd = platform_get_drvdata(pdev);
	struct ehci_hcd_mv *ehci_mv = hcd_to_ehci_hcd_mv(hcd);

	if (hcd->rh_registered)
		usb_remove_hcd(hcd);

	if (!IS_ERR_OR_NULL(ehci_mv->otg))
		otg_set_host(ehci_mv->otg->otg, NULL);

	if (ehci_mv->mode == MV_USB_MODE_HOST) {
		if (ehci_mv->set_vbus)
			ehci_mv->set_vbus(0);

		mv_ehci_disable(ehci_mv);
	}

	usb_put_hcd(hcd);

	return 0;
}