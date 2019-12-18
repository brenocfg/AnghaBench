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
struct myrs_hba {int /*<<< orphan*/  queue_lock; } ;
struct myrs_cmdblk {int /*<<< orphan*/ * complete; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete ; 
 int /*<<< orphan*/  in_interrupt () ; 
 int /*<<< orphan*/  myrs_qcmd (struct myrs_hba*,struct myrs_cmdblk*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void myrs_exec_cmd(struct myrs_hba *cs,
		struct myrs_cmdblk *cmd_blk)
{
	DECLARE_COMPLETION_ONSTACK(complete);
	unsigned long flags;

	cmd_blk->complete = &complete;
	spin_lock_irqsave(&cs->queue_lock, flags);
	myrs_qcmd(cs, cmd_blk);
	spin_unlock_irqrestore(&cs->queue_lock, flags);

	WARN_ON(in_interrupt());
	wait_for_completion(&complete);
}