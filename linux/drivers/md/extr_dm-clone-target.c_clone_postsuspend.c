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
struct dm_target {struct clone* private; } ;
struct clone {int /*<<< orphan*/  wq; int /*<<< orphan*/  hydrations_in_flight; int /*<<< orphan*/  hydration_stopped; int /*<<< orphan*/  flags; int /*<<< orphan*/  waker; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_CLONE_HYDRATION_SUSPENDED ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  commit_metadata (struct clone*) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void clone_postsuspend(struct dm_target *ti)
{
	struct clone *clone = ti->private;

	/*
	 * To successfully suspend the device:
	 *
	 *	- We cancel the delayed work for periodic commits and wait for
	 *	  it to finish.
	 *
	 *	- We stop the background hydration, i.e. we prevent new region
	 *	  hydrations from starting.
	 *
	 *	- We wait for any in-flight hydrations to finish.
	 *
	 *	- We flush the workqueue.
	 *
	 *	- We commit the metadata.
	 */
	cancel_delayed_work_sync(&clone->waker);

	set_bit(DM_CLONE_HYDRATION_SUSPENDED, &clone->flags);

	/*
	 * Make sure set_bit() is ordered before atomic_read(), otherwise we
	 * might race with do_hydration() and miss some started region
	 * hydrations.
	 *
	 * This is paired with smp_mb__after_atomic() in do_hydration().
	 */
	smp_mb__after_atomic();

	wait_event(clone->hydration_stopped, !atomic_read(&clone->hydrations_in_flight));
	flush_workqueue(clone->wq);

	(void) commit_metadata(clone);
}