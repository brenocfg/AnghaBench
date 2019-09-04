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
struct perf_sched {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __perf_sched_find_counter (struct perf_sched*) ; 
 int /*<<< orphan*/  perf_sched_restore_state (struct perf_sched*) ; 

__attribute__((used)) static bool perf_sched_find_counter(struct perf_sched *sched)
{
	while (!__perf_sched_find_counter(sched)) {
		if (!perf_sched_restore_state(sched))
			return false;
	}

	return true;
}