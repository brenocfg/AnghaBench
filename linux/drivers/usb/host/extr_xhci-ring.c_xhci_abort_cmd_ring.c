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
typedef  int u64 ;
struct xhci_hcd {int /*<<< orphan*/  lock; int /*<<< orphan*/  cmd_ring_stop_completion; TYPE_1__* op_regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  cmd_ring; } ;

/* Variables and functions */
 int CMD_RING_ABORT ; 
 int /*<<< orphan*/  CMD_RING_RUNNING ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_cleanup_command_queue (struct xhci_hcd*) ; 
 int /*<<< orphan*/  xhci_dbg (struct xhci_hcd*,char*) ; 
 int /*<<< orphan*/  xhci_err (struct xhci_hcd*,char*,int) ; 
 int /*<<< orphan*/  xhci_halt (struct xhci_hcd*) ; 
 int /*<<< orphan*/  xhci_handle_stopped_cmd_ring (struct xhci_hcd*,int /*<<< orphan*/ ) ; 
 int xhci_handshake (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xhci_hc_died (struct xhci_hcd*) ; 
 int /*<<< orphan*/  xhci_next_queued_cmd (struct xhci_hcd*) ; 
 int xhci_read_64 (struct xhci_hcd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xhci_write_64 (struct xhci_hcd*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int xhci_abort_cmd_ring(struct xhci_hcd *xhci, unsigned long flags)
{
	u64 temp_64;
	int ret;

	xhci_dbg(xhci, "Abort command ring\n");

	reinit_completion(&xhci->cmd_ring_stop_completion);

	temp_64 = xhci_read_64(xhci, &xhci->op_regs->cmd_ring);
	xhci_write_64(xhci, temp_64 | CMD_RING_ABORT,
			&xhci->op_regs->cmd_ring);

	/* Section 4.6.1.2 of xHCI 1.0 spec says software should also time the
	 * completion of the Command Abort operation. If CRR is not negated in 5
	 * seconds then driver handles it as if host died (-ENODEV).
	 * In the future we should distinguish between -ENODEV and -ETIMEDOUT
	 * and try to recover a -ETIMEDOUT with a host controller reset.
	 */
	ret = xhci_handshake(&xhci->op_regs->cmd_ring,
			CMD_RING_RUNNING, 0, 5 * 1000 * 1000);
	if (ret < 0) {
		xhci_err(xhci, "Abort failed to stop command ring: %d\n", ret);
		xhci_halt(xhci);
		xhci_hc_died(xhci);
		return ret;
	}
	/*
	 * Writing the CMD_RING_ABORT bit should cause a cmd completion event,
	 * however on some host hw the CMD_RING_RUNNING bit is correctly cleared
	 * but the completion event in never sent. Wait 2 secs (arbitrary
	 * number) to handle those cases after negation of CMD_RING_RUNNING.
	 */
	spin_unlock_irqrestore(&xhci->lock, flags);
	ret = wait_for_completion_timeout(&xhci->cmd_ring_stop_completion,
					  msecs_to_jiffies(2000));
	spin_lock_irqsave(&xhci->lock, flags);
	if (!ret) {
		xhci_dbg(xhci, "No stop event for abort, ring start fail?\n");
		xhci_cleanup_command_queue(xhci);
	} else {
		xhci_handle_stopped_cmd_ring(xhci, xhci_next_queued_cmd(xhci));
	}
	return 0;
}