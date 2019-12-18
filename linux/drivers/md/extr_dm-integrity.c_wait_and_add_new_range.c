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
struct dm_integrity_range {int waiting; int /*<<< orphan*/  task; int /*<<< orphan*/  wait_entry; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct dm_integrity_c {TYPE_1__ endio_wait; int /*<<< orphan*/  wait_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  io_schedule () ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void wait_and_add_new_range(struct dm_integrity_c *ic, struct dm_integrity_range *new_range)
{
	new_range->waiting = true;
	list_add_tail(&new_range->wait_entry, &ic->wait_list);
	new_range->task = current;
	do {
		__set_current_state(TASK_UNINTERRUPTIBLE);
		spin_unlock_irq(&ic->endio_wait.lock);
		io_schedule();
		spin_lock_irq(&ic->endio_wait.lock);
	} while (unlikely(new_range->waiting));
}