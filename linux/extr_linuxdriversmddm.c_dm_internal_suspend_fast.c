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
struct mapped_device {int /*<<< orphan*/  wq; int /*<<< orphan*/  io_barrier; int /*<<< orphan*/  flags; int /*<<< orphan*/  suspend_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMF_BLOCK_IO_FOR_SUSPEND ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 scalar_t__ dm_suspended_internally_md (struct mapped_device*) ; 
 scalar_t__ dm_suspended_md (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_wait_for_completion (struct mapped_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_srcu (int /*<<< orphan*/ *) ; 

void dm_internal_suspend_fast(struct mapped_device *md)
{
	mutex_lock(&md->suspend_lock);
	if (dm_suspended_md(md) || dm_suspended_internally_md(md))
		return;

	set_bit(DMF_BLOCK_IO_FOR_SUSPEND, &md->flags);
	synchronize_srcu(&md->io_barrier);
	flush_workqueue(md->wq);
	dm_wait_for_completion(md, TASK_UNINTERRUPTIBLE);
}