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
struct xhci_hcd {int xhc_state; int /*<<< orphan*/ * devs; int /*<<< orphan*/  hcs_params1; } ;

/* Variables and functions */
 int HCS_MAX_SLOTS (int /*<<< orphan*/ ) ; 
 int XHCI_STATE_DYING ; 
 int XHCI_STATE_REMOVING ; 
 int /*<<< orphan*/  usb_hc_died (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_cleanup_command_queue (struct xhci_hcd*) ; 
 int /*<<< orphan*/  xhci_err (struct xhci_hcd*,char*) ; 
 int /*<<< orphan*/  xhci_kill_endpoint_urbs (struct xhci_hcd*,int,int) ; 
 int /*<<< orphan*/  xhci_to_hcd (struct xhci_hcd*) ; 

void xhci_hc_died(struct xhci_hcd *xhci)
{
	int i, j;

	if (xhci->xhc_state & XHCI_STATE_DYING)
		return;

	xhci_err(xhci, "xHCI host controller not responding, assume dead\n");
	xhci->xhc_state |= XHCI_STATE_DYING;

	xhci_cleanup_command_queue(xhci);

	/* return any pending urbs, remove may be waiting for them */
	for (i = 0; i <= HCS_MAX_SLOTS(xhci->hcs_params1); i++) {
		if (!xhci->devs[i])
			continue;
		for (j = 0; j < 31; j++)
			xhci_kill_endpoint_urbs(xhci, i, j);
	}

	/* inform usb core hc died if PCI remove isn't already handling it */
	if (!(xhci->xhc_state & XHCI_STATE_REMOVING))
		usb_hc_died(xhci_to_hcd(xhci));
}