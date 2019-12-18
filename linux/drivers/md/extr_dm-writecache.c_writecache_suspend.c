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
struct dm_writecache {int flush_on_suspend; int /*<<< orphan*/  memory_map_size; int /*<<< orphan*/  memory_map; int /*<<< orphan*/  writeback_all; int /*<<< orphan*/  writeback_wq; int /*<<< orphan*/  writeback_work; int /*<<< orphan*/  autocommit_timer; } ;
struct dm_target {struct dm_writecache* private; } ;

/* Variables and functions */
 scalar_t__ WC_MODE_PMEM (struct dm_writecache*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  persistent_memory_flush_cache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wc_lock (struct dm_writecache*) ; 
 int /*<<< orphan*/  wc_unlock (struct dm_writecache*) ; 
 int /*<<< orphan*/  writecache_flush (struct dm_writecache*) ; 
 int /*<<< orphan*/  writecache_poison_lists (struct dm_writecache*) ; 
 scalar_t__ writecache_wait_for_writeback (struct dm_writecache*) ; 

__attribute__((used)) static void writecache_suspend(struct dm_target *ti)
{
	struct dm_writecache *wc = ti->private;
	bool flush_on_suspend;

	del_timer_sync(&wc->autocommit_timer);

	wc_lock(wc);
	writecache_flush(wc);
	flush_on_suspend = wc->flush_on_suspend;
	if (flush_on_suspend) {
		wc->flush_on_suspend = false;
		wc->writeback_all++;
		queue_work(wc->writeback_wq, &wc->writeback_work);
	}
	wc_unlock(wc);

	flush_workqueue(wc->writeback_wq);

	wc_lock(wc);
	if (flush_on_suspend)
		wc->writeback_all--;
	while (writecache_wait_for_writeback(wc));

	if (WC_MODE_PMEM(wc))
		persistent_memory_flush_cache(wc->memory_map, wc->memory_map_size);

	writecache_poison_lists(wc);

	wc_unlock(wc);
}