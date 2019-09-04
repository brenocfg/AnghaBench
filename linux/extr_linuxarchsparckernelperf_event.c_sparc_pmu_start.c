#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int state; } ;
struct perf_event {TYPE_1__ hw; } ;
struct cpu_hw_events {int dummy; } ;

/* Variables and functions */
 int PERF_EF_RELOAD ; 
 int PERF_HES_UPTODATE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int active_event_index (struct cpu_hw_events*,struct perf_event*) ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 int /*<<< orphan*/  perf_event_update_userpage (struct perf_event*) ; 
 int /*<<< orphan*/  sparc_perf_event_set_period (struct perf_event*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  sparc_pmu_enable_event (struct cpu_hw_events*,TYPE_1__*,int) ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sparc_pmu_start(struct perf_event *event, int flags)
{
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	int idx = active_event_index(cpuc, event);

	if (flags & PERF_EF_RELOAD) {
		WARN_ON_ONCE(!(event->hw.state & PERF_HES_UPTODATE));
		sparc_perf_event_set_period(event, &event->hw, idx);
	}

	event->hw.state = 0;

	sparc_pmu_enable_event(cpuc, &event->hw, idx);

	perf_event_update_userpage(event);
}