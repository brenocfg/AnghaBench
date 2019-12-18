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
struct xhci_virt_ep {int dummy; } ;
struct xhci_transfer_event {int /*<<< orphan*/  buffer; } ;
struct xhci_td {scalar_t__ last_trb; TYPE_1__* urb; } ;
struct xhci_ring {scalar_t__ dequeue; } ;
struct xhci_hcd {int dummy; } ;
struct usb_iso_packet_descriptor {scalar_t__ actual_length; int /*<<< orphan*/  status; } ;
struct urb_priv {int num_tds_done; } ;
struct TYPE_2__ {struct usb_iso_packet_descriptor* iso_frame_desc; struct urb_priv* hcpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXDEV ; 
 int /*<<< orphan*/  inc_deq (struct xhci_hcd*,struct xhci_ring*) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 struct xhci_ring* xhci_dma_to_transfer_ring (struct xhci_virt_ep*,int /*<<< orphan*/ ) ; 
 int xhci_td_cleanup (struct xhci_hcd*,struct xhci_td*,struct xhci_ring*,int*) ; 

__attribute__((used)) static int skip_isoc_td(struct xhci_hcd *xhci, struct xhci_td *td,
			struct xhci_transfer_event *event,
			struct xhci_virt_ep *ep, int *status)
{
	struct xhci_ring *ep_ring;
	struct urb_priv *urb_priv;
	struct usb_iso_packet_descriptor *frame;
	int idx;

	ep_ring = xhci_dma_to_transfer_ring(ep, le64_to_cpu(event->buffer));
	urb_priv = td->urb->hcpriv;
	idx = urb_priv->num_tds_done;
	frame = &td->urb->iso_frame_desc[idx];

	/* The transfer is partly done. */
	frame->status = -EXDEV;

	/* calc actual length */
	frame->actual_length = 0;

	/* Update ring dequeue pointer */
	while (ep_ring->dequeue != td->last_trb)
		inc_deq(xhci, ep_ring);
	inc_deq(xhci, ep_ring);

	return xhci_td_cleanup(xhci, td, ep_ring, status);
}