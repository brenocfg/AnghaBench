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
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct dm_integrity_c {TYPE_1__ endio_wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  __add_wait_queue (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __remove_wait_queue (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  io_schedule () ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static void sleep_on_endio_wait(struct dm_integrity_c *ic)
{
	DECLARE_WAITQUEUE(wait, current);
	__add_wait_queue(&ic->endio_wait, &wait);
	__set_current_state(TASK_UNINTERRUPTIBLE);
	spin_unlock_irq(&ic->endio_wait.lock);
	io_schedule();
	spin_lock_irq(&ic->endio_wait.lock);
	__remove_wait_queue(&ic->endio_wait, &wait);
}