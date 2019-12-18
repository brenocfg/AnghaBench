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
struct r10conf {int /*<<< orphan*/  resync_lock; int /*<<< orphan*/  nr_pending; int /*<<< orphan*/  wait_barrier; int /*<<< orphan*/  nr_waiting; scalar_t__ barrier; int /*<<< orphan*/  mddev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * bio_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_list_empty (int /*<<< orphan*/ *) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  raid10_log (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_lock_irq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wait_barrier(struct r10conf *conf)
{
	spin_lock_irq(&conf->resync_lock);
	if (conf->barrier) {
		conf->nr_waiting++;
		/* Wait for the barrier to drop.
		 * However if there are already pending
		 * requests (preventing the barrier from
		 * rising completely), and the
		 * pre-process bio queue isn't empty,
		 * then don't wait, as we need to empty
		 * that queue to get the nr_pending
		 * count down.
		 */
		raid10_log(conf->mddev, "wait barrier");
		wait_event_lock_irq(conf->wait_barrier,
				    !conf->barrier ||
				    (atomic_read(&conf->nr_pending) &&
				     current->bio_list &&
				     (!bio_list_empty(&current->bio_list[0]) ||
				      !bio_list_empty(&current->bio_list[1]))),
				    conf->resync_lock);
		conf->nr_waiting--;
		if (!conf->nr_waiting)
			wake_up(&conf->wait_barrier);
	}
	atomic_inc(&conf->nr_pending);
	spin_unlock_irq(&conf->resync_lock);
}