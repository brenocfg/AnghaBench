#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct xhci_hcd {int cmd_ring_reserved_trbs; int xhc_state; TYPE_1__* cmd_ring; int /*<<< orphan*/  cmd_list; struct xhci_command* current_cmd; } ;
struct xhci_command {int /*<<< orphan*/  cmd_list; int /*<<< orphan*/  command_trb; } ;
struct TYPE_3__ {int cycle_state; int /*<<< orphan*/  enqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  EP_STATE_RUNNING ; 
 int ESHUTDOWN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  XHCI_CMD_DEFAULT_TIMEOUT ; 
 int XHCI_STATE_DYING ; 
 int XHCI_STATE_HALTED ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int prepare_ring (struct xhci_hcd*,TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_trb (struct xhci_hcd*,TYPE_1__*,int,int,int,int,int) ; 
 int /*<<< orphan*/  xhci_dbg (struct xhci_hcd*,char*) ; 
 int /*<<< orphan*/  xhci_err (struct xhci_hcd*,char*) ; 
 int /*<<< orphan*/  xhci_mod_cmd_timer (struct xhci_hcd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int queue_command(struct xhci_hcd *xhci, struct xhci_command *cmd,
			 u32 field1, u32 field2,
			 u32 field3, u32 field4, bool command_must_succeed)
{
	int reserved_trbs = xhci->cmd_ring_reserved_trbs;
	int ret;

	if ((xhci->xhc_state & XHCI_STATE_DYING) ||
		(xhci->xhc_state & XHCI_STATE_HALTED)) {
		xhci_dbg(xhci, "xHCI dying or halted, can't queue_command\n");
		return -ESHUTDOWN;
	}

	if (!command_must_succeed)
		reserved_trbs++;

	ret = prepare_ring(xhci, xhci->cmd_ring, EP_STATE_RUNNING,
			reserved_trbs, GFP_ATOMIC);
	if (ret < 0) {
		xhci_err(xhci, "ERR: No room for command on command ring\n");
		if (command_must_succeed)
			xhci_err(xhci, "ERR: Reserved TRB counting for "
					"unfailable commands failed.\n");
		return ret;
	}

	cmd->command_trb = xhci->cmd_ring->enqueue;

	/* if there are no other commands queued we start the timeout timer */
	if (list_empty(&xhci->cmd_list)) {
		xhci->current_cmd = cmd;
		xhci_mod_cmd_timer(xhci, XHCI_CMD_DEFAULT_TIMEOUT);
	}

	list_add_tail(&cmd->cmd_list, &xhci->cmd_list);

	queue_trb(xhci, xhci->cmd_ring, false, field1, field2, field3,
			field4 | xhci->cmd_ring->cycle_state);
	return 0;
}