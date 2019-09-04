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
struct task_struct {int dummy; } ;
struct mmc_host {int claimed; int claim_cnt; int /*<<< orphan*/  wq; int /*<<< orphan*/  lock; } ;
struct mmc_ctx {int dummy; } ;
typedef  int /*<<< orphan*/  atomic_t ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,struct task_struct*) ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  might_sleep () ; 
 scalar_t__ mmc_ctx_matches (struct mmc_host*,struct mmc_ctx*,struct task_struct*) ; 
 int /*<<< orphan*/  mmc_ctx_set_claimer (struct mmc_host*,struct mmc_ctx*,struct task_struct*) ; 
 int /*<<< orphan*/  mmc_dev (struct mmc_host*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

int __mmc_claim_host(struct mmc_host *host, struct mmc_ctx *ctx,
		     atomic_t *abort)
{
	struct task_struct *task = ctx ? NULL : current;
	DECLARE_WAITQUEUE(wait, current);
	unsigned long flags;
	int stop;
	bool pm = false;

	might_sleep();

	add_wait_queue(&host->wq, &wait);
	spin_lock_irqsave(&host->lock, flags);
	while (1) {
		set_current_state(TASK_UNINTERRUPTIBLE);
		stop = abort ? atomic_read(abort) : 0;
		if (stop || !host->claimed || mmc_ctx_matches(host, ctx, task))
			break;
		spin_unlock_irqrestore(&host->lock, flags);
		schedule();
		spin_lock_irqsave(&host->lock, flags);
	}
	set_current_state(TASK_RUNNING);
	if (!stop) {
		host->claimed = 1;
		mmc_ctx_set_claimer(host, ctx, task);
		host->claim_cnt += 1;
		if (host->claim_cnt == 1)
			pm = true;
	} else
		wake_up(&host->wq);
	spin_unlock_irqrestore(&host->lock, flags);
	remove_wait_queue(&host->wq, &wait);

	if (pm)
		pm_runtime_get_sync(mmc_dev(host));

	return stop;
}