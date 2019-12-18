#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct list_head {TYPE_2__* prev; TYPE_1__* next; } ;
struct dm_writecache {int /*<<< orphan*/  dev; int /*<<< orphan*/  endio_list_lock; struct list_head endio_list; } ;
struct TYPE_4__ {struct list_head* next; } ;
struct TYPE_3__ {struct list_head* prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 int /*<<< orphan*/  READ ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  WC_MODE_FUA (struct dm_writecache*) ; 
 scalar_t__ WC_MODE_PMEM (struct dm_writecache*) ; 
 int /*<<< orphan*/  __writecache_endio_pmem (struct dm_writecache*,struct list_head*) ; 
 int /*<<< orphan*/  __writecache_endio_ssd (struct dm_writecache*,struct list_head*) ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  list_empty (struct list_head*) ; 
 int /*<<< orphan*/  raw_spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wc_lock (struct dm_writecache*) ; 
 int /*<<< orphan*/  wc_unlock (struct dm_writecache*) ; 
 int /*<<< orphan*/  writecache_commit_flushed (struct dm_writecache*) ; 
 int /*<<< orphan*/  writecache_disk_flush (struct dm_writecache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writecache_wait_for_ios (struct dm_writecache*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int writecache_endio_thread(void *data)
{
	struct dm_writecache *wc = data;

	while (1) {
		struct list_head list;

		raw_spin_lock_irq(&wc->endio_list_lock);
		if (!list_empty(&wc->endio_list))
			goto pop_from_list;
		set_current_state(TASK_INTERRUPTIBLE);
		raw_spin_unlock_irq(&wc->endio_list_lock);

		if (unlikely(kthread_should_stop())) {
			set_current_state(TASK_RUNNING);
			break;
		}

		schedule();

		continue;

pop_from_list:
		list = wc->endio_list;
		list.next->prev = list.prev->next = &list;
		INIT_LIST_HEAD(&wc->endio_list);
		raw_spin_unlock_irq(&wc->endio_list_lock);

		if (!WC_MODE_FUA(wc))
			writecache_disk_flush(wc, wc->dev);

		wc_lock(wc);

		if (WC_MODE_PMEM(wc)) {
			__writecache_endio_pmem(wc, &list);
		} else {
			__writecache_endio_ssd(wc, &list);
			writecache_wait_for_ios(wc, READ);
		}

		writecache_commit_flushed(wc);

		wc_unlock(wc);
	}

	return 0;
}