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
struct hwbus_priv {int claimed; int /*<<< orphan*/  wq; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static void cw1200_spi_lock(struct hwbus_priv *self)
{
	unsigned long flags;

	DECLARE_WAITQUEUE(wait, current);

	might_sleep();

	add_wait_queue(&self->wq, &wait);
	spin_lock_irqsave(&self->lock, flags);
	while (1) {
		set_current_state(TASK_UNINTERRUPTIBLE);
		if (!self->claimed)
			break;
		spin_unlock_irqrestore(&self->lock, flags);
		schedule();
		spin_lock_irqsave(&self->lock, flags);
	}
	set_current_state(TASK_RUNNING);
	self->claimed = 1;
	spin_unlock_irqrestore(&self->lock, flags);
	remove_wait_queue(&self->wq, &wait);

	return;
}