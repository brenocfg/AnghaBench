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
struct raw3215_info {int flags; int /*<<< orphan*/  cdev; int /*<<< orphan*/  port; int /*<<< orphan*/  empty_wait; int /*<<< orphan*/ * queued_read; int /*<<< orphan*/ * queued_write; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int RAW3215_FIXED ; 
 int RAW3215_WORKING ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  get_ccwdev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  tty_port_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_port_set_initialized (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static void raw3215_shutdown(struct raw3215_info *raw)
{
	DECLARE_WAITQUEUE(wait, current);
	unsigned long flags;

	if (!tty_port_initialized(&raw->port) || (raw->flags & RAW3215_FIXED))
		return;
	/* Wait for outstanding requests, then free irq */
	spin_lock_irqsave(get_ccwdev_lock(raw->cdev), flags);
	if ((raw->flags & RAW3215_WORKING) ||
	    raw->queued_write != NULL ||
	    raw->queued_read != NULL) {
		add_wait_queue(&raw->empty_wait, &wait);
		set_current_state(TASK_INTERRUPTIBLE);
		spin_unlock_irqrestore(get_ccwdev_lock(raw->cdev), flags);
		schedule();
		spin_lock_irqsave(get_ccwdev_lock(raw->cdev), flags);
		remove_wait_queue(&raw->empty_wait, &wait);
		set_current_state(TASK_RUNNING);
		tty_port_set_initialized(&raw->port, 1);
	}
	spin_unlock_irqrestore(get_ccwdev_lock(raw->cdev), flags);
}