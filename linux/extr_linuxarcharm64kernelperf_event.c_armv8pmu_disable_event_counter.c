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
struct hw_perf_event {int idx; } ;
struct perf_event {struct hw_perf_event hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  armv8pmu_disable_counter (int) ; 
 scalar_t__ armv8pmu_event_is_chained (struct perf_event*) ; 

__attribute__((used)) static inline void armv8pmu_disable_event_counter(struct perf_event *event)
{
	struct hw_perf_event *hwc = &event->hw;
	int idx = hwc->idx;

	if (armv8pmu_event_is_chained(event))
		armv8pmu_disable_counter(idx - 1);
	armv8pmu_disable_counter(idx);
}