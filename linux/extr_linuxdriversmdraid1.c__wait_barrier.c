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
struct r1conf {int /*<<< orphan*/  resync_lock; int /*<<< orphan*/ * nr_waiting; int /*<<< orphan*/ * nr_pending; int /*<<< orphan*/ * barrier; int /*<<< orphan*/  array_frozen; int /*<<< orphan*/  wait_barrier; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_lock_irq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _wait_barrier(struct r1conf *conf, int idx)
{
	/*
	 * We need to increase conf->nr_pending[idx] very early here,
	 * then raise_barrier() can be blocked when it waits for
	 * conf->nr_pending[idx] to be 0. Then we can avoid holding
	 * conf->resync_lock when there is no barrier raised in same
	 * barrier unit bucket. Also if the array is frozen, I/O
	 * should be blocked until array is unfrozen.
	 */
	atomic_inc(&conf->nr_pending[idx]);
	/*
	 * In _wait_barrier() we firstly increase conf->nr_pending[idx], then
	 * check conf->barrier[idx]. In raise_barrier() we firstly increase
	 * conf->barrier[idx], then check conf->nr_pending[idx]. A memory
	 * barrier is necessary here to make sure conf->barrier[idx] won't be
	 * fetched before conf->nr_pending[idx] is increased. Otherwise there
	 * will be a race between _wait_barrier() and raise_barrier().
	 */
	smp_mb__after_atomic();

	/*
	 * Don't worry about checking two atomic_t variables at same time
	 * here. If during we check conf->barrier[idx], the array is
	 * frozen (conf->array_frozen is 1), and chonf->barrier[idx] is
	 * 0, it is safe to return and make the I/O continue. Because the
	 * array is frozen, all I/O returned here will eventually complete
	 * or be queued, no race will happen. See code comment in
	 * frozen_array().
	 */
	if (!READ_ONCE(conf->array_frozen) &&
	    !atomic_read(&conf->barrier[idx]))
		return;

	/*
	 * After holding conf->resync_lock, conf->nr_pending[idx]
	 * should be decreased before waiting for barrier to drop.
	 * Otherwise, we may encounter a race condition because
	 * raise_barrer() might be waiting for conf->nr_pending[idx]
	 * to be 0 at same time.
	 */
	spin_lock_irq(&conf->resync_lock);
	atomic_inc(&conf->nr_waiting[idx]);
	atomic_dec(&conf->nr_pending[idx]);
	/*
	 * In case freeze_array() is waiting for
	 * get_unqueued_pending() == extra
	 */
	wake_up(&conf->wait_barrier);
	/* Wait for the barrier in same barrier unit bucket to drop. */
	wait_event_lock_irq(conf->wait_barrier,
			    !conf->array_frozen &&
			     !atomic_read(&conf->barrier[idx]),
			    conf->resync_lock);
	atomic_inc(&conf->nr_pending[idx]);
	atomic_dec(&conf->nr_waiting[idx]);
	spin_unlock_irq(&conf->resync_lock);
}