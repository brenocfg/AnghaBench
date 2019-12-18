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
struct xhci_td {int /*<<< orphan*/  cancelled_td_list; int /*<<< orphan*/  td_list; struct urb* urb; } ;
struct xhci_ring {int dummy; } ;
struct xhci_hcd {int dummy; } ;
struct urb {scalar_t__ actual_length; scalar_t__ transfer_buffer_length; int transfer_flags; int /*<<< orphan*/  pipe; TYPE_1__* ep; } ;
struct TYPE_2__ {int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 scalar_t__ PIPE_ISOCHRONOUS ; 
 int URB_SHORT_NOT_OK ; 
 int /*<<< orphan*/  inc_td_cnt (struct urb*) ; 
 scalar_t__ last_td_in_urb (struct xhci_td*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_endpoint_xfer_isoc (int /*<<< orphan*/ *) ; 
 scalar_t__ usb_pipetype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_dbg (struct xhci_hcd*,char*,struct urb*,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  xhci_giveback_urb_in_irq (struct xhci_hcd*,struct xhci_td*,int) ; 
 int /*<<< orphan*/  xhci_unmap_td_bounce_buffer (struct xhci_hcd*,struct xhci_ring*,struct xhci_td*) ; 
 int /*<<< orphan*/  xhci_warn (struct xhci_hcd*,char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int xhci_td_cleanup(struct xhci_hcd *xhci, struct xhci_td *td,
		struct xhci_ring *ep_ring, int *status)
{
	struct urb *urb = NULL;

	/* Clean up the endpoint's TD list */
	urb = td->urb;

	/* if a bounce buffer was used to align this td then unmap it */
	xhci_unmap_td_bounce_buffer(xhci, ep_ring, td);

	/* Do one last check of the actual transfer length.
	 * If the host controller said we transferred more data than the buffer
	 * length, urb->actual_length will be a very big number (since it's
	 * unsigned).  Play it safe and say we didn't transfer anything.
	 */
	if (urb->actual_length > urb->transfer_buffer_length) {
		xhci_warn(xhci, "URB req %u and actual %u transfer length mismatch\n",
			  urb->transfer_buffer_length, urb->actual_length);
		urb->actual_length = 0;
		*status = 0;
	}
	list_del_init(&td->td_list);
	/* Was this TD slated to be cancelled but completed anyway? */
	if (!list_empty(&td->cancelled_td_list))
		list_del_init(&td->cancelled_td_list);

	inc_td_cnt(urb);
	/* Giveback the urb when all the tds are completed */
	if (last_td_in_urb(td)) {
		if ((urb->actual_length != urb->transfer_buffer_length &&
		     (urb->transfer_flags & URB_SHORT_NOT_OK)) ||
		    (*status != 0 && !usb_endpoint_xfer_isoc(&urb->ep->desc)))
			xhci_dbg(xhci, "Giveback URB %p, len = %d, expected = %d, status = %d\n",
				 urb, urb->actual_length,
				 urb->transfer_buffer_length, *status);

		/* set isoc urb status to 0 just as EHCI, UHCI, and OHCI */
		if (usb_pipetype(urb->pipe) == PIPE_ISOCHRONOUS)
			*status = 0;
		xhci_giveback_urb_in_irq(xhci, td, *status);
	}

	return 0;
}