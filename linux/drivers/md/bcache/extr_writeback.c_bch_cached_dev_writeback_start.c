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
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct cached_dev {int writeback_running; int writeback_rate_update_seconds; int /*<<< orphan*/  writeback_rate_update; TYPE_1__ disk; int /*<<< orphan*/  writeback_thread; int /*<<< orphan*/  writeback_write_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCACHE_DEV_WB_RUNNING ; 
 int ENOMEM ; 
 int HZ ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WQ_MEM_RECLAIM ; 
 int /*<<< orphan*/  alloc_workqueue (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bch_writeback_queue (struct cached_dev*) ; 
 int /*<<< orphan*/  bch_writeback_thread ; 
 int /*<<< orphan*/  cached_dev_get (struct cached_dev*) ; 
 int /*<<< orphan*/  cached_dev_put (struct cached_dev*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_create (int /*<<< orphan*/ ,struct cached_dev*,char*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int bch_cached_dev_writeback_start(struct cached_dev *dc)
{
	dc->writeback_write_wq = alloc_workqueue("bcache_writeback_wq",
						WQ_MEM_RECLAIM, 0);
	if (!dc->writeback_write_wq)
		return -ENOMEM;

	cached_dev_get(dc);
	dc->writeback_thread = kthread_create(bch_writeback_thread, dc,
					      "bcache_writeback");
	if (IS_ERR(dc->writeback_thread)) {
		cached_dev_put(dc);
		destroy_workqueue(dc->writeback_write_wq);
		return PTR_ERR(dc->writeback_thread);
	}
	dc->writeback_running = true;

	WARN_ON(test_and_set_bit(BCACHE_DEV_WB_RUNNING, &dc->disk.flags));
	schedule_delayed_work(&dc->writeback_rate_update,
			      dc->writeback_rate_update_seconds * HZ);

	bch_writeback_queue(dc);

	return 0;
}