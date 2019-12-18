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
struct usb_hcd {scalar_t__ irq; TYPE_1__* driver; int /*<<< orphan*/  flags; } ;
struct pci_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* shutdown ) (struct usb_hcd*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HCD_FLAG_HW_ACCESSIBLE ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct usb_hcd*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct usb_hcd* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  stub1 (struct usb_hcd*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ usb_hcd_is_primary_hcd (struct usb_hcd*) ; 

void usb_hcd_pci_shutdown(struct pci_dev *dev)
{
	struct usb_hcd		*hcd;

	hcd = pci_get_drvdata(dev);
	if (!hcd)
		return;

	if (test_bit(HCD_FLAG_HW_ACCESSIBLE, &hcd->flags) &&
			hcd->driver->shutdown) {
		hcd->driver->shutdown(hcd);
		if (usb_hcd_is_primary_hcd(hcd) && hcd->irq > 0)
			free_irq(hcd->irq, hcd);
		pci_disable_device(dev);
	}
}