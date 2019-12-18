#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * field; } ;
union xhci_trb {TYPE_3__ generic; } ;
typedef  int /*<<< orphan*/  u32 ;
struct xhci_virt_device {TYPE_2__* eps; TYPE_1__* in_ctx; int /*<<< orphan*/  out_ctx; } ;
struct xhci_hcd {int quirks; struct xhci_virt_device** devs; } ;
struct xhci_ep_ctx {int dummy; } ;
struct xhci_command {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  ep_state; } ;
struct TYPE_4__ {int /*<<< orphan*/  dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  EP_HALTED ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 unsigned int TRB_TO_EP_INDEX (int) ; 
 int TRB_TSP ; 
 int XHCI_RESET_EP_QUIRK ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ring_doorbell_for_active_rings (struct xhci_hcd*,int,unsigned int) ; 
 int /*<<< orphan*/  trace_xhci_dbg_quirks ; 
 int /*<<< orphan*/  trace_xhci_dbg_reset_ep ; 
 int /*<<< orphan*/  trace_xhci_handle_cmd_reset_ep (struct xhci_ep_ctx*) ; 
 struct xhci_command* xhci_alloc_command (struct xhci_hcd*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_dbg_trace (struct xhci_hcd*,int /*<<< orphan*/ ,char*,...) ; 
 struct xhci_ep_ctx* xhci_get_ep_ctx (struct xhci_hcd*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  xhci_queue_configure_endpoint (struct xhci_hcd*,struct xhci_command*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  xhci_ring_cmd_db (struct xhci_hcd*) ; 

__attribute__((used)) static void xhci_handle_cmd_reset_ep(struct xhci_hcd *xhci, int slot_id,
		union xhci_trb *trb, u32 cmd_comp_code)
{
	struct xhci_virt_device *vdev;
	struct xhci_ep_ctx *ep_ctx;
	unsigned int ep_index;

	ep_index = TRB_TO_EP_INDEX(le32_to_cpu(trb->generic.field[3]));
	vdev = xhci->devs[slot_id];
	ep_ctx = xhci_get_ep_ctx(xhci, vdev->out_ctx, ep_index);
	trace_xhci_handle_cmd_reset_ep(ep_ctx);

	/* This command will only fail if the endpoint wasn't halted,
	 * but we don't care.
	 */
	xhci_dbg_trace(xhci, trace_xhci_dbg_reset_ep,
		"Ignoring reset ep completion code of %u", cmd_comp_code);

	/* HW with the reset endpoint quirk needs to have a configure endpoint
	 * command complete before the endpoint can be used.  Queue that here
	 * because the HW can't handle two commands being queued in a row.
	 */
	if (xhci->quirks & XHCI_RESET_EP_QUIRK) {
		struct xhci_command *command;

		command = xhci_alloc_command(xhci, false, GFP_ATOMIC);
		if (!command)
			return;

		xhci_dbg_trace(xhci, trace_xhci_dbg_quirks,
				"Queueing configure endpoint command");
		xhci_queue_configure_endpoint(xhci, command,
				xhci->devs[slot_id]->in_ctx->dma, slot_id,
				false);
		xhci_ring_cmd_db(xhci);
	} else {
		/* Clear our internal halted state */
		xhci->devs[slot_id]->eps[ep_index].ep_state &= ~EP_HALTED;
	}

	/* if this was a soft reset, then restart */
	if ((le32_to_cpu(trb->generic.field[3])) & TRB_TSP)
		ring_doorbell_for_active_rings(xhci, slot_id, ep_index);
}