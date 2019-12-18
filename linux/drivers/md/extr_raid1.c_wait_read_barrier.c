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
struct r1conf {int /*<<< orphan*/  resync_lock; int /*<<< orphan*/ * nr_waiting; int /*<<< orphan*/ * nr_pending; int /*<<< orphan*/  array_frozen; int /*<<< orphan*/  wait_barrier; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int sector_to_idx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_lock_irq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wait_read_barrier(struct r1conf *conf, sector_t sector_nr)
{
	int idx = sector_to_idx(sector_nr);

	/*
	 * Very similar to _wait_barrier(). The difference is, for read
	 * I/O we don't need wait for sync I/O, but if the whole array
	 * is frozen, the read I/O still has to wait until the array is
	 * unfrozen. Since there is no ordering requirement with
	 * conf->barrier[idx] here, memory barrier is unnecessary as well.
	 */
	atomic_inc(&conf->nr_pending[idx]);

	if (!READ_ONCE(conf->array_frozen))
		return;

	spin_lock_irq(&conf->resync_lock);
	atomic_inc(&conf->nr_waiting[idx]);
	atomic_dec(&conf->nr_pending[idx]);
	/*
	 * In case freeze_array() is waiting for
	 * get_unqueued_pending() == extra
	 */
	wake_up(&conf->wait_barrier);
	/* Wait for array to be unfrozen */
	wait_event_lock_irq(conf->wait_barrier,
			    !conf->array_frozen,
			    conf->resync_lock);
	atomic_inc(&conf->nr_pending[idx]);
	atomic_dec(&conf->nr_waiting[idx]);
	spin_unlock_irq(&conf->resync_lock);
}