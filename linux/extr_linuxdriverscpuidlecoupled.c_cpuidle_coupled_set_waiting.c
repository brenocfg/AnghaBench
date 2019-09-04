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
struct cpuidle_coupled {int* requested_state; int /*<<< orphan*/  ready_waiting_counts; } ;

/* Variables and functions */
 int WAITING_MASK ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cpuidle_coupled_set_waiting(int cpu,
		struct cpuidle_coupled *coupled, int next_state)
{
	coupled->requested_state[cpu] = next_state;

	/*
	 * The atomic_inc_return provides a write barrier to order the write
	 * to requested_state with the later write that increments ready_count.
	 */
	return atomic_inc_return(&coupled->ready_waiting_counts) & WAITING_MASK;
}