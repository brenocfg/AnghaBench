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
struct xhci_hcd {int /*<<< orphan*/  quirks; } ;
struct usb_hcd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XHCI_RESET_ON_RESUME ; 
 struct xhci_hcd* hcd_to_xhci (struct usb_hcd*) ; 

int xhci_mvebu_a3700_init_quirk(struct usb_hcd *hcd)
{
	struct xhci_hcd	*xhci = hcd_to_xhci(hcd);

	/* Without reset on resume, the HC won't work at all */
	xhci->quirks |= XHCI_RESET_ON_RESUME;

	return 0;
}