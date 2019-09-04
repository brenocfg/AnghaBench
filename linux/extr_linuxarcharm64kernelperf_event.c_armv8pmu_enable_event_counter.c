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
struct TYPE_2__ {int idx; } ;
struct perf_event {TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  armv8pmu_enable_counter (int) ; 
 scalar_t__ armv8pmu_event_is_chained (struct perf_event*) ; 
 int /*<<< orphan*/  isb () ; 

__attribute__((used)) static inline void armv8pmu_enable_event_counter(struct perf_event *event)
{
	int idx = event->hw.idx;

	armv8pmu_enable_counter(idx);
	if (armv8pmu_event_is_chained(event))
		armv8pmu_enable_counter(idx - 1);
	isb();
}