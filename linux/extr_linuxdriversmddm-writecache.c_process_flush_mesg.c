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
struct dm_writecache {int /*<<< orphan*/  writeback_all; int /*<<< orphan*/  writeback_wq; int /*<<< orphan*/  writeback_work; int /*<<< orphan*/  ti; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 scalar_t__ dm_suspended (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wc_lock (struct dm_writecache*) ; 
 int /*<<< orphan*/  wc_unlock (struct dm_writecache*) ; 
 int /*<<< orphan*/  writecache_flush (struct dm_writecache*) ; 
 scalar_t__ writecache_has_error (struct dm_writecache*) ; 

__attribute__((used)) static int process_flush_mesg(unsigned argc, char **argv, struct dm_writecache *wc)
{
	if (argc != 1)
		return -EINVAL;

	wc_lock(wc);
	if (dm_suspended(wc->ti)) {
		wc_unlock(wc);
		return -EBUSY;
	}
	if (writecache_has_error(wc)) {
		wc_unlock(wc);
		return -EIO;
	}

	writecache_flush(wc);
	wc->writeback_all++;
	queue_work(wc->writeback_wq, &wc->writeback_work);
	wc_unlock(wc);

	flush_workqueue(wc->writeback_wq);

	wc_lock(wc);
	wc->writeback_all--;
	if (writecache_has_error(wc)) {
		wc_unlock(wc);
		return -EIO;
	}
	wc_unlock(wc);

	return 0;
}