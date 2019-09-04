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
struct perf_event {int dummy; } ;
struct cpu_hw_events {struct amd_nb* amd_nb; } ;
struct amd_nb {scalar_t__ owners; } ;
struct TYPE_2__ {int num_counters; } ;

/* Variables and functions */
 struct perf_event* cmpxchg (scalar_t__,struct perf_event*,int /*<<< orphan*/ *) ; 
 TYPE_1__ x86_pmu ; 

__attribute__((used)) static void __amd_put_nb_event_constraints(struct cpu_hw_events *cpuc,
					   struct perf_event *event)
{
	struct amd_nb *nb = cpuc->amd_nb;
	int i;

	/*
	 * need to scan whole list because event may not have
	 * been assigned during scheduling
	 *
	 * no race condition possible because event can only
	 * be removed on one CPU at a time AND PMU is disabled
	 * when we come here
	 */
	for (i = 0; i < x86_pmu.num_counters; i++) {
		if (cmpxchg(nb->owners + i, event, NULL) == event)
			break;
	}
}