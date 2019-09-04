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
struct TYPE_2__ {int /*<<< orphan*/  prev_count; int /*<<< orphan*/  event_base; } ;
struct perf_event {TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  event_is_checkpointed (struct perf_event*) ; 
 int /*<<< orphan*/  local64_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int x86_perf_event_set_period (struct perf_event*) ; 
 int /*<<< orphan*/  x86_perf_event_update (struct perf_event*) ; 

int intel_pmu_save_and_restart(struct perf_event *event)
{
	x86_perf_event_update(event);
	/*
	 * For a checkpointed counter always reset back to 0.  This
	 * avoids a situation where the counter overflows, aborts the
	 * transaction and is then set back to shortly before the
	 * overflow, and overflows and aborts again.
	 */
	if (unlikely(event_is_checkpointed(event))) {
		/* No race with NMIs because the counter should not be armed */
		wrmsrl(event->hw.event_base, 0);
		local64_set(&event->hw.prev_count, 0);
	}
	return x86_perf_event_set_period(event);
}