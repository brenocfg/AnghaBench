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
struct cpuidle_coupled {int /*<<< orphan*/ * requested_state; int /*<<< orphan*/  ready_waiting_counts; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUIDLE_COUPLED_NOT_IDLE ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cpuidle_coupled_set_not_waiting(int cpu,
		struct cpuidle_coupled *coupled)
{
	/*
	 * Decrementing waiting count can race with incrementing it in
	 * cpuidle_coupled_set_waiting, but that's OK.  Worst case, some
	 * cpus will increment ready_count and then spin until they
	 * notice that this cpu has cleared it's requested_state.
	 */
	atomic_dec(&coupled->ready_waiting_counts);

	coupled->requested_state[cpu] = CPUIDLE_COUPLED_NOT_IDLE;
}