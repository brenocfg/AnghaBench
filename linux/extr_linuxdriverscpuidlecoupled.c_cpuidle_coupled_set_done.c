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
struct cpuidle_coupled {int /*<<< orphan*/  ready_waiting_counts; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_WAITING_CPUS ; 
 int /*<<< orphan*/  atomic_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpuidle_coupled_set_not_waiting (int,struct cpuidle_coupled*) ; 

__attribute__((used)) static void cpuidle_coupled_set_done(int cpu, struct cpuidle_coupled *coupled)
{
	cpuidle_coupled_set_not_waiting(cpu, coupled);
	atomic_sub(MAX_WAITING_CPUS, &coupled->ready_waiting_counts);
}