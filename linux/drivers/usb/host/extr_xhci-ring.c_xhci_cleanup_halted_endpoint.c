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
struct xhci_virt_ep {int /*<<< orphan*/  ep_state; } ;
struct xhci_td {int dummy; } ;
struct xhci_hcd {TYPE_1__** devs; } ;
struct xhci_command {int dummy; } ;
typedef  enum xhci_ep_reset_type { ____Placeholder_xhci_ep_reset_type } xhci_ep_reset_type ;
struct TYPE_2__ {int flags; struct xhci_virt_ep* eps; } ;

/* Variables and functions */
 int /*<<< orphan*/  EP_HALTED ; 
 int /*<<< orphan*/  EP_HARD_CLEAR_TOGGLE ; 
 int EP_HARD_RESET ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int VDEV_PORT_ERROR ; 
 struct xhci_command* xhci_alloc_command (struct xhci_hcd*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_cleanup_stalled_ring (struct xhci_hcd*,unsigned int,unsigned int,struct xhci_td*) ; 
 int /*<<< orphan*/  xhci_clear_hub_tt_buffer (struct xhci_hcd*,struct xhci_td*,struct xhci_virt_ep*) ; 
 int /*<<< orphan*/  xhci_queue_reset_ep (struct xhci_hcd*,struct xhci_command*,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  xhci_ring_cmd_db (struct xhci_hcd*) ; 

__attribute__((used)) static void xhci_cleanup_halted_endpoint(struct xhci_hcd *xhci,
		unsigned int slot_id, unsigned int ep_index,
		unsigned int stream_id, struct xhci_td *td,
		enum xhci_ep_reset_type reset_type)
{
	struct xhci_virt_ep *ep = &xhci->devs[slot_id]->eps[ep_index];
	struct xhci_command *command;

	/*
	 * Avoid resetting endpoint if link is inactive. Can cause host hang.
	 * Device will be reset soon to recover the link so don't do anything
	 */
	if (xhci->devs[slot_id]->flags & VDEV_PORT_ERROR)
		return;

	command = xhci_alloc_command(xhci, false, GFP_ATOMIC);
	if (!command)
		return;

	ep->ep_state |= EP_HALTED;

	xhci_queue_reset_ep(xhci, command, slot_id, ep_index, reset_type);

	if (reset_type == EP_HARD_RESET) {
		ep->ep_state |= EP_HARD_CLEAR_TOGGLE;
		xhci_cleanup_stalled_ring(xhci, ep_index, stream_id, td);
		xhci_clear_hub_tt_buffer(xhci, td, ep);
	}
	xhci_ring_cmd_db(xhci);
}