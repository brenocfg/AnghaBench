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
struct clone {unsigned long nr_regions; unsigned long hydration_offset; int /*<<< orphan*/  hydrations_in_flight; int /*<<< orphan*/  hydration_threshold; int /*<<< orphan*/  flags; int /*<<< orphan*/  ios_in_flight; int /*<<< orphan*/  cmd; } ;
struct batch_info {scalar_t__ nr_batched_regions; int /*<<< orphan*/ * head; } ;

/* Variables and functions */
 scalar_t__ CM_READ_ONLY ; 
 int /*<<< orphan*/  DM_CLONE_HYDRATION_ENABLED ; 
 int /*<<< orphan*/  DM_CLONE_HYDRATION_SUSPENDED ; 
 unsigned int READ_ONCE (int /*<<< orphan*/ ) ; 
 unsigned long __start_next_hydration (struct clone*,unsigned long,struct batch_info*) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 unsigned int atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ dm_clone_is_hydration_done (int /*<<< orphan*/ ) ; 
 scalar_t__ get_clone_mode (struct clone*) ; 
 int /*<<< orphan*/  hydration_copy (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wakeup_hydration_waiters (struct clone*) ; 

__attribute__((used)) static void do_hydration(struct clone *clone)
{
	unsigned int current_volume;
	unsigned long offset, nr_regions = clone->nr_regions;

	struct batch_info batch = {
		.head = NULL,
		.nr_batched_regions = 0,
	};

	if (unlikely(get_clone_mode(clone) >= CM_READ_ONLY))
		return;

	if (dm_clone_is_hydration_done(clone->cmd))
		return;

	/*
	 * Avoid race with device suspension.
	 */
	atomic_inc(&clone->hydrations_in_flight);

	/*
	 * Make sure atomic_inc() is ordered before test_bit(), otherwise we
	 * might race with clone_postsuspend() and start a region hydration
	 * after the target has been suspended.
	 *
	 * This is paired with the smp_mb__after_atomic() in
	 * clone_postsuspend().
	 */
	smp_mb__after_atomic();

	offset = clone->hydration_offset;
	while (likely(!test_bit(DM_CLONE_HYDRATION_SUSPENDED, &clone->flags)) &&
	       !atomic_read(&clone->ios_in_flight) &&
	       test_bit(DM_CLONE_HYDRATION_ENABLED, &clone->flags) &&
	       offset < nr_regions) {
		current_volume = atomic_read(&clone->hydrations_in_flight);
		current_volume += batch.nr_batched_regions;

		if (current_volume > READ_ONCE(clone->hydration_threshold))
			break;

		offset = __start_next_hydration(clone, offset, &batch);
	}

	if (batch.head)
		hydration_copy(batch.head, batch.nr_batched_regions);

	if (offset >= nr_regions)
		offset = 0;

	clone->hydration_offset = offset;

	if (atomic_dec_and_test(&clone->hydrations_in_flight))
		wakeup_hydration_waiters(clone);
}