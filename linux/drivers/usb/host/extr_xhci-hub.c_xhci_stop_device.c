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
struct xhci_virt_device {int /*<<< orphan*/  out_ctx; TYPE_2__* eps; } ;
struct xhci_hcd {int /*<<< orphan*/  lock; struct xhci_virt_device** devs; } ;
struct xhci_ep_ctx {int dummy; } ;
struct xhci_command {scalar_t__ status; int /*<<< orphan*/  completion; } ;
struct TYPE_4__ {TYPE_1__* ring; } ;
struct TYPE_3__ {scalar_t__ dequeue; } ;

/* Variables and functions */
 scalar_t__ COMP_COMMAND_ABORTED ; 
 scalar_t__ COMP_COMMAND_RING_STOPPED ; 
 int ENODEV ; 
 int ENOMEM ; 
 scalar_t__ EP_STATE_RUNNING ; 
 int ETIME ; 
 scalar_t__ GET_EP_CTX_STATE (struct xhci_ep_ctx*) ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int LAST_EP_INDEX ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  trace_xhci_stop_device (struct xhci_virt_device*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ ) ; 
 struct xhci_command* xhci_alloc_command (struct xhci_hcd*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_free_command (struct xhci_hcd*,struct xhci_command*) ; 
 struct xhci_ep_ctx* xhci_get_ep_ctx (struct xhci_hcd*,int /*<<< orphan*/ ,int) ; 
 int xhci_queue_stop_endpoint (struct xhci_hcd*,struct xhci_command*,int,int,int) ; 
 int /*<<< orphan*/  xhci_ring_cmd_db (struct xhci_hcd*) ; 
 int /*<<< orphan*/  xhci_warn (struct xhci_hcd*,char*) ; 

__attribute__((used)) static int xhci_stop_device(struct xhci_hcd *xhci, int slot_id, int suspend)
{
	struct xhci_virt_device *virt_dev;
	struct xhci_command *cmd;
	unsigned long flags;
	int ret;
	int i;

	ret = 0;
	virt_dev = xhci->devs[slot_id];
	if (!virt_dev)
		return -ENODEV;

	trace_xhci_stop_device(virt_dev);

	cmd = xhci_alloc_command(xhci, true, GFP_NOIO);
	if (!cmd)
		return -ENOMEM;

	spin_lock_irqsave(&xhci->lock, flags);
	for (i = LAST_EP_INDEX; i > 0; i--) {
		if (virt_dev->eps[i].ring && virt_dev->eps[i].ring->dequeue) {
			struct xhci_ep_ctx *ep_ctx;
			struct xhci_command *command;

			ep_ctx = xhci_get_ep_ctx(xhci, virt_dev->out_ctx, i);

			/* Check ep is running, required by AMD SNPS 3.1 xHC */
			if (GET_EP_CTX_STATE(ep_ctx) != EP_STATE_RUNNING)
				continue;

			command = xhci_alloc_command(xhci, false, GFP_NOWAIT);
			if (!command) {
				spin_unlock_irqrestore(&xhci->lock, flags);
				ret = -ENOMEM;
				goto cmd_cleanup;
			}

			ret = xhci_queue_stop_endpoint(xhci, command, slot_id,
						       i, suspend);
			if (ret) {
				spin_unlock_irqrestore(&xhci->lock, flags);
				xhci_free_command(xhci, command);
				goto cmd_cleanup;
			}
		}
	}
	ret = xhci_queue_stop_endpoint(xhci, cmd, slot_id, 0, suspend);
	if (ret) {
		spin_unlock_irqrestore(&xhci->lock, flags);
		goto cmd_cleanup;
	}

	xhci_ring_cmd_db(xhci);
	spin_unlock_irqrestore(&xhci->lock, flags);

	/* Wait for last stop endpoint command to finish */
	wait_for_completion(cmd->completion);

	if (cmd->status == COMP_COMMAND_ABORTED ||
	    cmd->status == COMP_COMMAND_RING_STOPPED) {
		xhci_warn(xhci, "Timeout while waiting for stop endpoint command\n");
		ret = -ETIME;
	}

cmd_cleanup:
	xhci_free_command(xhci, cmd);
	return ret;
}