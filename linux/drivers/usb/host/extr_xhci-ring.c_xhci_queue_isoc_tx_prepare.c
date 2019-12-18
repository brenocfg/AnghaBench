#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xhci_virt_ep {int next_frame_id; struct xhci_ring* ring; } ;
struct xhci_virt_device {int /*<<< orphan*/  out_ctx; struct xhci_virt_ep* eps; } ;
struct xhci_ring {int /*<<< orphan*/  num_trbs_free; int /*<<< orphan*/  num_trbs_free_temp; int /*<<< orphan*/  td_list; } ;
struct xhci_hcd {int /*<<< orphan*/  hcs_params2; TYPE_1__* run_regs; int /*<<< orphan*/  hcc_params; struct xhci_virt_device** devs; } ;
struct xhci_ep_ctx {int dummy; } ;
struct urb {int number_of_packets; int start_frame; int interval; TYPE_2__* dev; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_4__ {scalar_t__ speed; } ;
struct TYPE_3__ {int /*<<< orphan*/  microframe_index; } ;

/* Variables and functions */
 scalar_t__ EP_STATE_RUNNING ; 
 scalar_t__ GET_EP_CTX_STATE (struct xhci_ep_ctx*) ; 
 scalar_t__ HCC_CFC (int /*<<< orphan*/ ) ; 
 int HCS_IST (int /*<<< orphan*/ ) ; 
 scalar_t__ USB_SPEED_FULL ; 
 scalar_t__ USB_SPEED_LOW ; 
 scalar_t__ XHCI_CFC_DELAY ; 
 int /*<<< orphan*/  check_interval (struct xhci_hcd*,struct urb*,struct xhci_ep_ctx*) ; 
 scalar_t__ count_isoc_trbs_needed (struct urb*,int) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int prepare_ring (struct xhci_hcd*,struct xhci_ring*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int readl (int /*<<< orphan*/ *) ; 
 int roundup (int,int) ; 
 struct xhci_ep_ctx* xhci_get_ep_ctx (struct xhci_hcd*,int /*<<< orphan*/ ,unsigned int) ; 
 int xhci_queue_isoc_tx (struct xhci_hcd*,int /*<<< orphan*/ ,struct urb*,int,unsigned int) ; 

int xhci_queue_isoc_tx_prepare(struct xhci_hcd *xhci, gfp_t mem_flags,
		struct urb *urb, int slot_id, unsigned int ep_index)
{
	struct xhci_virt_device *xdev;
	struct xhci_ring *ep_ring;
	struct xhci_ep_ctx *ep_ctx;
	int start_frame;
	int num_tds, num_trbs, i;
	int ret;
	struct xhci_virt_ep *xep;
	int ist;

	xdev = xhci->devs[slot_id];
	xep = &xhci->devs[slot_id]->eps[ep_index];
	ep_ring = xdev->eps[ep_index].ring;
	ep_ctx = xhci_get_ep_ctx(xhci, xdev->out_ctx, ep_index);

	num_trbs = 0;
	num_tds = urb->number_of_packets;
	for (i = 0; i < num_tds; i++)
		num_trbs += count_isoc_trbs_needed(urb, i);

	/* Check the ring to guarantee there is enough room for the whole urb.
	 * Do not insert any td of the urb to the ring if the check failed.
	 */
	ret = prepare_ring(xhci, ep_ring, GET_EP_CTX_STATE(ep_ctx),
			   num_trbs, mem_flags);
	if (ret)
		return ret;

	/*
	 * Check interval value. This should be done before we start to
	 * calculate the start frame value.
	 */
	check_interval(xhci, urb, ep_ctx);

	/* Calculate the start frame and put it in urb->start_frame. */
	if (HCC_CFC(xhci->hcc_params) && !list_empty(&ep_ring->td_list)) {
		if (GET_EP_CTX_STATE(ep_ctx) ==	EP_STATE_RUNNING) {
			urb->start_frame = xep->next_frame_id;
			goto skip_start_over;
		}
	}

	start_frame = readl(&xhci->run_regs->microframe_index);
	start_frame &= 0x3fff;
	/*
	 * Round up to the next frame and consider the time before trb really
	 * gets scheduled by hardare.
	 */
	ist = HCS_IST(xhci->hcs_params2) & 0x7;
	if (HCS_IST(xhci->hcs_params2) & (1 << 3))
		ist <<= 3;
	start_frame += ist + XHCI_CFC_DELAY;
	start_frame = roundup(start_frame, 8);

	/*
	 * Round up to the next ESIT (Endpoint Service Interval Time) if ESIT
	 * is greate than 8 microframes.
	 */
	if (urb->dev->speed == USB_SPEED_LOW ||
			urb->dev->speed == USB_SPEED_FULL) {
		start_frame = roundup(start_frame, urb->interval << 3);
		urb->start_frame = start_frame >> 3;
	} else {
		start_frame = roundup(start_frame, urb->interval);
		urb->start_frame = start_frame;
	}

skip_start_over:
	ep_ring->num_trbs_free_temp = ep_ring->num_trbs_free;

	return xhci_queue_isoc_tx(xhci, mem_flags, urb, slot_id, ep_index);
}