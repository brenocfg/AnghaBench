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
struct r1conf {int /*<<< orphan*/  resync_lock; int /*<<< orphan*/  nr_sync_pending; int /*<<< orphan*/  wait_barrier; int /*<<< orphan*/ * barrier; TYPE_1__* mddev; int /*<<< orphan*/ * nr_pending; int /*<<< orphan*/  array_frozen; int /*<<< orphan*/ * nr_waiting; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_2__ {int /*<<< orphan*/  recovery; } ;

/* Variables and functions */
 int EINTR ; 
 int /*<<< orphan*/  MD_RECOVERY_INTR ; 
 scalar_t__ RESYNC_DEPTH ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int sector_to_idx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_lock_irq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int raise_barrier(struct r1conf *conf, sector_t sector_nr)
{
	int idx = sector_to_idx(sector_nr);

	spin_lock_irq(&conf->resync_lock);

	/* Wait until no block IO is waiting */
	wait_event_lock_irq(conf->wait_barrier,
			    !atomic_read(&conf->nr_waiting[idx]),
			    conf->resync_lock);

	/* block any new IO from starting */
	atomic_inc(&conf->barrier[idx]);
	/*
	 * In raise_barrier() we firstly increase conf->barrier[idx] then
	 * check conf->nr_pending[idx]. In _wait_barrier() we firstly
	 * increase conf->nr_pending[idx] then check conf->barrier[idx].
	 * A memory barrier here to make sure conf->nr_pending[idx] won't
	 * be fetched before conf->barrier[idx] is increased. Otherwise
	 * there will be a race between raise_barrier() and _wait_barrier().
	 */
	smp_mb__after_atomic();

	/* For these conditions we must wait:
	 * A: while the array is in frozen state
	 * B: while conf->nr_pending[idx] is not 0, meaning regular I/O
	 *    existing in corresponding I/O barrier bucket.
	 * C: while conf->barrier[idx] >= RESYNC_DEPTH, meaning reaches
	 *    max resync count which allowed on current I/O barrier bucket.
	 */
	wait_event_lock_irq(conf->wait_barrier,
			    (!conf->array_frozen &&
			     !atomic_read(&conf->nr_pending[idx]) &&
			     atomic_read(&conf->barrier[idx]) < RESYNC_DEPTH) ||
				test_bit(MD_RECOVERY_INTR, &conf->mddev->recovery),
			    conf->resync_lock);

	if (test_bit(MD_RECOVERY_INTR, &conf->mddev->recovery)) {
		atomic_dec(&conf->barrier[idx]);
		spin_unlock_irq(&conf->resync_lock);
		wake_up(&conf->wait_barrier);
		return -EINTR;
	}

	atomic_inc(&conf->nr_sync_pending);
	spin_unlock_irq(&conf->resync_lock);

	return 0;
}