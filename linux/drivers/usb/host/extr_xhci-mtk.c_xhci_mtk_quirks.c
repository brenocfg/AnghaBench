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
struct xhci_hcd_mtk {scalar_t__ lpm_support; } ;
struct xhci_hcd {int /*<<< orphan*/  quirks; } ;
struct usb_hcd {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XHCI_LPM_SUPPORT ; 
 int /*<<< orphan*/  XHCI_MTK_HOST ; 
 int /*<<< orphan*/  XHCI_PLAT ; 
 int /*<<< orphan*/  XHCI_SPURIOUS_SUCCESS ; 
 struct xhci_hcd_mtk* hcd_to_mtk (struct usb_hcd*) ; 
 struct usb_hcd* xhci_to_hcd (struct xhci_hcd*) ; 

__attribute__((used)) static void xhci_mtk_quirks(struct device *dev, struct xhci_hcd *xhci)
{
	struct usb_hcd *hcd = xhci_to_hcd(xhci);
	struct xhci_hcd_mtk *mtk = hcd_to_mtk(hcd);

	/*
	 * As of now platform drivers don't provide MSI support so we ensure
	 * here that the generic code does not try to make a pci_dev from our
	 * dev struct in order to setup MSI
	 */
	xhci->quirks |= XHCI_PLAT;
	xhci->quirks |= XHCI_MTK_HOST;
	/*
	 * MTK host controller gives a spurious successful event after a
	 * short transfer. Ignore it.
	 */
	xhci->quirks |= XHCI_SPURIOUS_SUCCESS;
	if (mtk->lpm_support)
		xhci->quirks |= XHCI_LPM_SUPPORT;
}