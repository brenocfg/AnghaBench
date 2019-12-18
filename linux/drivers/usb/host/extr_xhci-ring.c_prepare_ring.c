#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct xhci_ring {unsigned int num_trbs_free; scalar_t__ type; int cycle_state; TYPE_2__* enq_seg; TYPE_3__* enqueue; } ;
struct xhci_hcd {int quirks; struct xhci_ring* cmd_ring; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_5__ {int /*<<< orphan*/  control; } ;
struct TYPE_7__ {TYPE_1__ link; } ;
struct TYPE_6__ {TYPE_3__* trbs; struct TYPE_6__* next; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
#define  EP_STATE_DISABLED 132 
#define  EP_STATE_ERROR 131 
#define  EP_STATE_HALTED 130 
#define  EP_STATE_RUNNING 129 
#define  EP_STATE_STOPPED 128 
 int /*<<< orphan*/  TRB_CHAIN ; 
 int /*<<< orphan*/  TRB_CYCLE ; 
 scalar_t__ TYPE_ISOC ; 
 int XHCI_AMD_0x96_HOST ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 scalar_t__ link_trb_toggles_cycle (TYPE_3__*) ; 
 scalar_t__ room_on_ring (struct xhci_hcd*,struct xhci_ring*,unsigned int) ; 
 int /*<<< orphan*/  trace_xhci_dbg_ring_expansion ; 
 scalar_t__ trb_is_link (TYPE_3__*) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  xhci_dbg (struct xhci_hcd*,char*) ; 
 int /*<<< orphan*/  xhci_dbg_trace (struct xhci_hcd*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xhci_err (struct xhci_hcd*,char*) ; 
 int /*<<< orphan*/  xhci_link_trb_quirk (struct xhci_hcd*) ; 
 scalar_t__ xhci_ring_expansion (struct xhci_hcd*,struct xhci_ring*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_warn (struct xhci_hcd*,char*) ; 

__attribute__((used)) static int prepare_ring(struct xhci_hcd *xhci, struct xhci_ring *ep_ring,
		u32 ep_state, unsigned int num_trbs, gfp_t mem_flags)
{
	unsigned int num_trbs_needed;

	/* Make sure the endpoint has been added to xHC schedule */
	switch (ep_state) {
	case EP_STATE_DISABLED:
		/*
		 * USB core changed config/interfaces without notifying us,
		 * or hardware is reporting the wrong state.
		 */
		xhci_warn(xhci, "WARN urb submitted to disabled ep\n");
		return -ENOENT;
	case EP_STATE_ERROR:
		xhci_warn(xhci, "WARN waiting for error on ep to be cleared\n");
		/* FIXME event handling code for error needs to clear it */
		/* XXX not sure if this should be -ENOENT or not */
		return -EINVAL;
	case EP_STATE_HALTED:
		xhci_dbg(xhci, "WARN halted endpoint, queueing URB anyway.\n");
	case EP_STATE_STOPPED:
	case EP_STATE_RUNNING:
		break;
	default:
		xhci_err(xhci, "ERROR unknown endpoint state for ep\n");
		/*
		 * FIXME issue Configure Endpoint command to try to get the HC
		 * back into a known state.
		 */
		return -EINVAL;
	}

	while (1) {
		if (room_on_ring(xhci, ep_ring, num_trbs))
			break;

		if (ep_ring == xhci->cmd_ring) {
			xhci_err(xhci, "Do not support expand command ring\n");
			return -ENOMEM;
		}

		xhci_dbg_trace(xhci, trace_xhci_dbg_ring_expansion,
				"ERROR no room on ep ring, try ring expansion");
		num_trbs_needed = num_trbs - ep_ring->num_trbs_free;
		if (xhci_ring_expansion(xhci, ep_ring, num_trbs_needed,
					mem_flags)) {
			xhci_err(xhci, "Ring expansion failed\n");
			return -ENOMEM;
		}
	}

	while (trb_is_link(ep_ring->enqueue)) {
		/* If we're not dealing with 0.95 hardware or isoc rings
		 * on AMD 0.96 host, clear the chain bit.
		 */
		if (!xhci_link_trb_quirk(xhci) &&
		    !(ep_ring->type == TYPE_ISOC &&
		      (xhci->quirks & XHCI_AMD_0x96_HOST)))
			ep_ring->enqueue->link.control &=
				cpu_to_le32(~TRB_CHAIN);
		else
			ep_ring->enqueue->link.control |=
				cpu_to_le32(TRB_CHAIN);

		wmb();
		ep_ring->enqueue->link.control ^= cpu_to_le32(TRB_CYCLE);

		/* Toggle the cycle bit after the last ring segment. */
		if (link_trb_toggles_cycle(ep_ring->enqueue))
			ep_ring->cycle_state ^= 1;

		ep_ring->enq_seg = ep_ring->enq_seg->next;
		ep_ring->enqueue = ep_ring->enq_seg->trbs;
	}
	return 0;
}