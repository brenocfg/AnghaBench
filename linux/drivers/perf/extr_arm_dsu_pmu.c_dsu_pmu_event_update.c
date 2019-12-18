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
typedef  scalar_t__ u64 ;
struct hw_perf_event {int /*<<< orphan*/  idx; int /*<<< orphan*/  prev_count; } ;
struct perf_event {int /*<<< orphan*/  count; struct hw_perf_event hw; } ;

/* Variables and functions */
 scalar_t__ DSU_PMU_COUNTER_MASK (int /*<<< orphan*/ ) ; 
 scalar_t__ dsu_pmu_read_counter (struct perf_event*) ; 
 int /*<<< orphan*/  local64_add (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ local64_cmpxchg (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 scalar_t__ local64_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dsu_pmu_event_update(struct perf_event *event)
{
	struct hw_perf_event *hwc = &event->hw;
	u64 delta, prev_count, new_count;

	do {
		/* We may also be called from the irq handler */
		prev_count = local64_read(&hwc->prev_count);
		new_count = dsu_pmu_read_counter(event);
	} while (local64_cmpxchg(&hwc->prev_count, prev_count, new_count) !=
			prev_count);
	delta = (new_count - prev_count) & DSU_PMU_COUNTER_MASK(hwc->idx);
	local64_add(delta, &event->count);
}