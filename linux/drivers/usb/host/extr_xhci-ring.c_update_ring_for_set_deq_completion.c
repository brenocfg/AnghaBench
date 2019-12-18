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
typedef  union xhci_trb {int dummy; } xhci_trb ;
struct xhci_virt_device {TYPE_1__* eps; } ;
struct xhci_ring {int num_trbs_free; union xhci_trb* dequeue; TYPE_2__* deq_seg; } ;
struct xhci_hcd {int dummy; } ;
struct TYPE_4__ {union xhci_trb* trbs; struct TYPE_4__* next; } ;
struct TYPE_3__ {union xhci_trb* queued_deq_ptr; } ;

/* Variables and functions */
 scalar_t__ trb_is_link (union xhci_trb*) ; 
 int /*<<< orphan*/  xhci_dbg (struct xhci_hcd*,char*) ; 

__attribute__((used)) static void update_ring_for_set_deq_completion(struct xhci_hcd *xhci,
		struct xhci_virt_device *dev,
		struct xhci_ring *ep_ring,
		unsigned int ep_index)
{
	union xhci_trb *dequeue_temp;
	int num_trbs_free_temp;
	bool revert = false;

	num_trbs_free_temp = ep_ring->num_trbs_free;
	dequeue_temp = ep_ring->dequeue;

	/* If we get two back-to-back stalls, and the first stalled transfer
	 * ends just before a link TRB, the dequeue pointer will be left on
	 * the link TRB by the code in the while loop.  So we have to update
	 * the dequeue pointer one segment further, or we'll jump off
	 * the segment into la-la-land.
	 */
	if (trb_is_link(ep_ring->dequeue)) {
		ep_ring->deq_seg = ep_ring->deq_seg->next;
		ep_ring->dequeue = ep_ring->deq_seg->trbs;
	}

	while (ep_ring->dequeue != dev->eps[ep_index].queued_deq_ptr) {
		/* We have more usable TRBs */
		ep_ring->num_trbs_free++;
		ep_ring->dequeue++;
		if (trb_is_link(ep_ring->dequeue)) {
			if (ep_ring->dequeue ==
					dev->eps[ep_index].queued_deq_ptr)
				break;
			ep_ring->deq_seg = ep_ring->deq_seg->next;
			ep_ring->dequeue = ep_ring->deq_seg->trbs;
		}
		if (ep_ring->dequeue == dequeue_temp) {
			revert = true;
			break;
		}
	}

	if (revert) {
		xhci_dbg(xhci, "Unable to find new dequeue pointer\n");
		ep_ring->num_trbs_free = num_trbs_free_temp;
	}
}