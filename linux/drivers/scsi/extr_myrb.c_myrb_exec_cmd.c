#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct myrb_hba {int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  (* qcmd ) (struct myrb_hba*,struct myrb_cmdblk*) ;} ;
struct myrb_cmdblk {unsigned short status; int /*<<< orphan*/ * completion; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmpl ; 
 int /*<<< orphan*/  in_interrupt () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct myrb_hba*,struct myrb_cmdblk*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned short myrb_exec_cmd(struct myrb_hba *cb,
		struct myrb_cmdblk *cmd_blk)
{
	DECLARE_COMPLETION_ONSTACK(cmpl);
	unsigned long flags;

	cmd_blk->completion = &cmpl;

	spin_lock_irqsave(&cb->queue_lock, flags);
	cb->qcmd(cb, cmd_blk);
	spin_unlock_irqrestore(&cb->queue_lock, flags);

	WARN_ON(in_interrupt());
	wait_for_completion(&cmpl);
	return cmd_blk->status;
}