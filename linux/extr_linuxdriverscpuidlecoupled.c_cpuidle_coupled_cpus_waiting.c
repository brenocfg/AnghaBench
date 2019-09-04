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
struct cpuidle_coupled {int online_count; int /*<<< orphan*/  ready_waiting_counts; } ;

/* Variables and functions */
 int WAITING_MASK ; 
 int atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool cpuidle_coupled_cpus_waiting(struct cpuidle_coupled *coupled)
{
	int w = atomic_read(&coupled->ready_waiting_counts) & WAITING_MASK;
	return w == coupled->online_count;
}