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
struct perf_event {int dummy; } ;

/* Variables and functions */
 struct perf_event** per_cpu (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perf_event_release_kernel (struct perf_event*) ; 
 int /*<<< orphan*/  perf_events ; 

__attribute__((used)) static void op_destroy_counter(int cpu, int event)
{
	struct perf_event *pevent = per_cpu(perf_events, cpu)[event];

	if (pevent) {
		perf_event_release_kernel(pevent);
		per_cpu(perf_events, cpu)[event] = NULL;
	}
}