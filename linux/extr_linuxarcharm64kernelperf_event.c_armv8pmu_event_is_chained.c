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
 int ARMV8_IDX_CYCLE_COUNTER ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ armv8pmu_event_is_64bit (struct perf_event*) ; 

__attribute__((used)) static inline bool armv8pmu_event_is_chained(struct perf_event *event)
{
	int idx = event->hw.idx;

	return !WARN_ON(idx < 0) &&
	       armv8pmu_event_is_64bit(event) &&
	       (idx != ARMV8_IDX_CYCLE_COUNTER);
}