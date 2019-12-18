#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * field; } ;
union xhci_trb {TYPE_2__ generic; } ;
typedef  int u32 ;
struct xhci_virt_ep {int dummy; } ;
struct xhci_transfer_event {int /*<<< orphan*/  transfer_len; int /*<<< orphan*/  buffer; int /*<<< orphan*/  flags; } ;
struct xhci_td {TYPE_5__* urb; union xhci_trb* last_trb; } ;
struct xhci_slot_ctx {int /*<<< orphan*/  tt_info; } ;
struct xhci_ring {int /*<<< orphan*/  stream_id; int /*<<< orphan*/  err_count; } ;
struct xhci_hcd {TYPE_1__** devs; } ;
struct TYPE_10__ {int transfer_buffer_length; int actual_length; TYPE_4__* ep; } ;
struct TYPE_8__ {int /*<<< orphan*/  bEndpointAddress; } ;
struct TYPE_9__ {TYPE_3__ desc; } ;
struct TYPE_6__ {int /*<<< orphan*/  out_ctx; } ;

/* Variables and functions */
#define  COMP_SHORT_PACKET 132 
#define  COMP_STOPPED_LENGTH_INVALID 131 
#define  COMP_STOPPED_SHORT_PACKET 130 
#define  COMP_SUCCESS 129 
#define  COMP_USB_TRANSACTION_ERROR 128 
 int /*<<< orphan*/  EP_SOFT_RESET ; 
 int EVENT_TRB_LEN (int) ; 
 int GET_COMP_CODE (int) ; 
 int /*<<< orphan*/  MAX_SOFT_RETRY ; 
 int TRB_LEN (int) ; 
 int TRB_TO_EP_ID (int) ; 
 unsigned int TRB_TO_SLOT_ID (int) ; 
 int TT_SLOT ; 
 int finish_td (struct xhci_hcd*,struct xhci_td*,struct xhci_transfer_event*,struct xhci_virt_ep*,int*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int sum_trb_lengths (struct xhci_hcd*,struct xhci_ring*,union xhci_trb*) ; 
 int /*<<< orphan*/  xhci_cleanup_halted_endpoint (struct xhci_hcd*,unsigned int,int,int /*<<< orphan*/ ,struct xhci_td*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_dbg (struct xhci_hcd*,char*,int /*<<< orphan*/ ,int,int) ; 
 struct xhci_ring* xhci_dma_to_transfer_ring (struct xhci_virt_ep*,int /*<<< orphan*/ ) ; 
 struct xhci_slot_ctx* xhci_get_slot_ctx (struct xhci_hcd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_warn (struct xhci_hcd*,char*,...) ; 

__attribute__((used)) static int process_bulk_intr_td(struct xhci_hcd *xhci, struct xhci_td *td,
	union xhci_trb *ep_trb, struct xhci_transfer_event *event,
	struct xhci_virt_ep *ep, int *status)
{
	struct xhci_slot_ctx *slot_ctx;
	struct xhci_ring *ep_ring;
	u32 trb_comp_code;
	u32 remaining, requested, ep_trb_len;
	unsigned int slot_id;
	int ep_index;

	slot_id = TRB_TO_SLOT_ID(le32_to_cpu(event->flags));
	slot_ctx = xhci_get_slot_ctx(xhci, xhci->devs[slot_id]->out_ctx);
	ep_index = TRB_TO_EP_ID(le32_to_cpu(event->flags)) - 1;
	ep_ring = xhci_dma_to_transfer_ring(ep, le64_to_cpu(event->buffer));
	trb_comp_code = GET_COMP_CODE(le32_to_cpu(event->transfer_len));
	remaining = EVENT_TRB_LEN(le32_to_cpu(event->transfer_len));
	ep_trb_len = TRB_LEN(le32_to_cpu(ep_trb->generic.field[2]));
	requested = td->urb->transfer_buffer_length;

	switch (trb_comp_code) {
	case COMP_SUCCESS:
		ep_ring->err_count = 0;
		/* handle success with untransferred data as short packet */
		if (ep_trb != td->last_trb || remaining) {
			xhci_warn(xhci, "WARN Successful completion on short TX\n");
			xhci_dbg(xhci, "ep %#x - asked for %d bytes, %d bytes untransferred\n",
				 td->urb->ep->desc.bEndpointAddress,
				 requested, remaining);
		}
		*status = 0;
		break;
	case COMP_SHORT_PACKET:
		xhci_dbg(xhci, "ep %#x - asked for %d bytes, %d bytes untransferred\n",
			 td->urb->ep->desc.bEndpointAddress,
			 requested, remaining);
		*status = 0;
		break;
	case COMP_STOPPED_SHORT_PACKET:
		td->urb->actual_length = remaining;
		goto finish_td;
	case COMP_STOPPED_LENGTH_INVALID:
		/* stopped on ep trb with invalid length, exclude it */
		ep_trb_len	= 0;
		remaining	= 0;
		break;
	case COMP_USB_TRANSACTION_ERROR:
		if ((ep_ring->err_count++ > MAX_SOFT_RETRY) ||
		    le32_to_cpu(slot_ctx->tt_info) & TT_SLOT)
			break;
		*status = 0;
		xhci_cleanup_halted_endpoint(xhci, slot_id, ep_index,
					ep_ring->stream_id, td, EP_SOFT_RESET);
		return 0;
	default:
		/* do nothing */
		break;
	}

	if (ep_trb == td->last_trb)
		td->urb->actual_length = requested - remaining;
	else
		td->urb->actual_length =
			sum_trb_lengths(xhci, ep_ring, ep_trb) +
			ep_trb_len - remaining;
finish_td:
	if (remaining > requested) {
		xhci_warn(xhci, "bad transfer trb length %d in event trb\n",
			  remaining);
		td->urb->actual_length = 0;
	}
	return finish_td(xhci, td, event, ep, status);
}