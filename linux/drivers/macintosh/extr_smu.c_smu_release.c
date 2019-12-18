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
struct TYPE_2__ {int status; } ;
struct smu_private {unsigned int busy; int /*<<< orphan*/  list; int /*<<< orphan*/  lock; int /*<<< orphan*/  wait; TYPE_1__ cmd; int /*<<< orphan*/  mode; } ;
struct inode {int dummy; } ;
struct file {struct smu_private* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  kfree (struct smu_private*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smu_clist_lock ; 
 int /*<<< orphan*/  smu_file_closing ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int smu_release(struct inode *inode, struct file *file)
{
	struct smu_private *pp = file->private_data;
	unsigned long flags;
	unsigned int busy;

	if (pp == 0)
		return 0;

	file->private_data = NULL;

	/* Mark file as closing to avoid races with new request */
	spin_lock_irqsave(&pp->lock, flags);
	pp->mode = smu_file_closing;
	busy = pp->busy;

	/* Wait for any pending request to complete */
	if (busy && pp->cmd.status == 1) {
		DECLARE_WAITQUEUE(wait, current);

		add_wait_queue(&pp->wait, &wait);
		for (;;) {
			set_current_state(TASK_UNINTERRUPTIBLE);
			if (pp->cmd.status != 1)
				break;
			spin_unlock_irqrestore(&pp->lock, flags);
			schedule();
			spin_lock_irqsave(&pp->lock, flags);
		}
		set_current_state(TASK_RUNNING);
		remove_wait_queue(&pp->wait, &wait);
	}
	spin_unlock_irqrestore(&pp->lock, flags);

	spin_lock_irqsave(&smu_clist_lock, flags);
	list_del(&pp->list);
	spin_unlock_irqrestore(&smu_clist_lock, flags);
	kfree(pp);

	return 0;
}