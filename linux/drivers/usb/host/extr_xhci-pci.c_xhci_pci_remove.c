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
struct xhci_hcd {int quirks; int /*<<< orphan*/ * shared_hcd; int /*<<< orphan*/  xhc_state; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_D3hot ; 
 int XHCI_DEFAULT_PM_RUNTIME_ALLOW ; 
 int XHCI_SPURIOUS_WAKEUP ; 
 int /*<<< orphan*/  XHCI_STATE_REMOVING ; 
 struct xhci_hcd* hcd_to_xhci (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_power_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_forbid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_hcd_pci_remove (struct pci_dev*) ; 
 int /*<<< orphan*/  usb_put_hcd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_remove_hcd (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xhci_pci_remove(struct pci_dev *dev)
{
	struct xhci_hcd *xhci;

	xhci = hcd_to_xhci(pci_get_drvdata(dev));
	xhci->xhc_state |= XHCI_STATE_REMOVING;

	if (xhci->quirks & XHCI_DEFAULT_PM_RUNTIME_ALLOW)
		pm_runtime_forbid(&dev->dev);

	if (xhci->shared_hcd) {
		usb_remove_hcd(xhci->shared_hcd);
		usb_put_hcd(xhci->shared_hcd);
		xhci->shared_hcd = NULL;
	}

	/* Workaround for spurious wakeups at shutdown with HSW */
	if (xhci->quirks & XHCI_SPURIOUS_WAKEUP)
		pci_set_power_state(dev, PCI_D3hot);

	usb_hcd_pci_remove(dev);
}