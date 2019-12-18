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
typedef  scalar_t__ u32 ;
struct bfa_mbox_cmd {int /*<<< orphan*/  msg; int /*<<< orphan*/  qe; void* cbarg; int /*<<< orphan*/  cbfn; } ;
struct bfa_ioc_mbox_mod {int /*<<< orphan*/  cmd_q; } ;
struct TYPE_2__ {int /*<<< orphan*/  hfn_mbox_cmd; } ;
struct bfa_ioc {TYPE_1__ ioc_regs; struct bfa_ioc_mbox_mod mbox_mod; } ;
typedef  int /*<<< orphan*/  bfa_mbox_cmd_cbfn_t ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_ioc_mbox_send (struct bfa_ioc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ readl (int /*<<< orphan*/ ) ; 

bool
bfa_nw_ioc_mbox_queue(struct bfa_ioc *ioc, struct bfa_mbox_cmd *cmd,
			bfa_mbox_cmd_cbfn_t cbfn, void *cbarg)
{
	struct bfa_ioc_mbox_mod *mod = &ioc->mbox_mod;
	u32			stat;

	cmd->cbfn = cbfn;
	cmd->cbarg = cbarg;

	/**
	 * If a previous command is pending, queue new command
	 */
	if (!list_empty(&mod->cmd_q)) {
		list_add_tail(&cmd->qe, &mod->cmd_q);
		return true;
	}

	/**
	 * If mailbox is busy, queue command for poll timer
	 */
	stat = readl(ioc->ioc_regs.hfn_mbox_cmd);
	if (stat) {
		list_add_tail(&cmd->qe, &mod->cmd_q);
		return true;
	}

	/**
	 * mailbox is free -- queue command to firmware
	 */
	bfa_ioc_mbox_send(ioc, cmd->msg, sizeof(cmd->msg));

	return false;
}