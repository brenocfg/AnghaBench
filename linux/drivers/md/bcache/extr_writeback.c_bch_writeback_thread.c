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
struct TYPE_4__ {int /*<<< orphan*/  flags; struct cache_set* c; } ;
struct TYPE_3__ {int /*<<< orphan*/  keys; } ;
struct cached_dev {unsigned int writeback_delay; scalar_t__ writeback_write_wq; int /*<<< orphan*/  writeback_rate; TYPE_2__ disk; int /*<<< orphan*/  writeback_lock; int /*<<< orphan*/  sb; int /*<<< orphan*/  has_dirty; TYPE_1__ writeback_keys; int /*<<< orphan*/  writeback_running; } ;
struct cache_set {int gc_after_writeback; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCACHE_DEV_DETACHING ; 
 int BCH_DO_AUTO_GC ; 
 int BCH_ENABLE_AUTO_GC ; 
 int /*<<< orphan*/  BDEV_STATE_CLEAN ; 
 int /*<<< orphan*/  CACHE_SET_IO_DISABLE ; 
 unsigned int HZ ; 
 scalar_t__ RB_EMPTY_ROOT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SET_BDEV_STATE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bch_ratelimit_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bch_write_bdev_super (struct cached_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cached_dev_put (struct cached_dev*) ; 
 int /*<<< orphan*/  destroy_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  force_wake_up_gc (struct cache_set*) ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  read_dirty (struct cached_dev*) ; 
 int refill_dirty (struct cached_dev*) ; 
 int /*<<< orphan*/  schedule () ; 
 unsigned int schedule_timeout_interruptible (unsigned int) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_kthread_stop () ; 

__attribute__((used)) static int bch_writeback_thread(void *arg)
{
	struct cached_dev *dc = arg;
	struct cache_set *c = dc->disk.c;
	bool searched_full_index;

	bch_ratelimit_reset(&dc->writeback_rate);

	while (!kthread_should_stop() &&
	       !test_bit(CACHE_SET_IO_DISABLE, &c->flags)) {
		down_write(&dc->writeback_lock);
		set_current_state(TASK_INTERRUPTIBLE);
		/*
		 * If the bache device is detaching, skip here and continue
		 * to perform writeback. Otherwise, if no dirty data on cache,
		 * or there is dirty data on cache but writeback is disabled,
		 * the writeback thread should sleep here and wait for others
		 * to wake up it.
		 */
		if (!test_bit(BCACHE_DEV_DETACHING, &dc->disk.flags) &&
		    (!atomic_read(&dc->has_dirty) || !dc->writeback_running)) {
			up_write(&dc->writeback_lock);

			if (kthread_should_stop() ||
			    test_bit(CACHE_SET_IO_DISABLE, &c->flags)) {
				set_current_state(TASK_RUNNING);
				break;
			}

			schedule();
			continue;
		}
		set_current_state(TASK_RUNNING);

		searched_full_index = refill_dirty(dc);

		if (searched_full_index &&
		    RB_EMPTY_ROOT(&dc->writeback_keys.keys)) {
			atomic_set(&dc->has_dirty, 0);
			SET_BDEV_STATE(&dc->sb, BDEV_STATE_CLEAN);
			bch_write_bdev_super(dc, NULL);
			/*
			 * If bcache device is detaching via sysfs interface,
			 * writeback thread should stop after there is no dirty
			 * data on cache. BCACHE_DEV_DETACHING flag is set in
			 * bch_cached_dev_detach().
			 */
			if (test_bit(BCACHE_DEV_DETACHING, &dc->disk.flags)) {
				up_write(&dc->writeback_lock);
				break;
			}

			/*
			 * When dirty data rate is high (e.g. 50%+), there might
			 * be heavy buckets fragmentation after writeback
			 * finished, which hurts following write performance.
			 * If users really care about write performance they
			 * may set BCH_ENABLE_AUTO_GC via sysfs, then when
			 * BCH_DO_AUTO_GC is set, garbage collection thread
			 * will be wake up here. After moving gc, the shrunk
			 * btree and discarded free buckets SSD space may be
			 * helpful for following write requests.
			 */
			if (c->gc_after_writeback ==
			    (BCH_ENABLE_AUTO_GC|BCH_DO_AUTO_GC)) {
				c->gc_after_writeback &= ~BCH_DO_AUTO_GC;
				force_wake_up_gc(c);
			}
		}

		up_write(&dc->writeback_lock);

		read_dirty(dc);

		if (searched_full_index) {
			unsigned int delay = dc->writeback_delay * HZ;

			while (delay &&
			       !kthread_should_stop() &&
			       !test_bit(CACHE_SET_IO_DISABLE, &c->flags) &&
			       !test_bit(BCACHE_DEV_DETACHING, &dc->disk.flags))
				delay = schedule_timeout_interruptible(delay);

			bch_ratelimit_reset(&dc->writeback_rate);
		}
	}

	if (dc->writeback_write_wq) {
		flush_workqueue(dc->writeback_write_wq);
		destroy_workqueue(dc->writeback_write_wq);
	}
	cached_dev_put(dc);
	wait_for_kthread_stop();

	return 0;
}