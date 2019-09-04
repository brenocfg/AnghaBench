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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int idx; } ;
struct perf_event {TYPE_1__ hw; } ;

/* Variables and functions */
 scalar_t__ armv8pmu_event_is_chained (struct perf_event*) ; 
 int /*<<< orphan*/  armv8pmu_write_evcntr (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void armv8pmu_write_hw_counter(struct perf_event *event,
					     u64 value)
{
	int idx = event->hw.idx;

	if (armv8pmu_event_is_chained(event)) {
		armv8pmu_write_evcntr(idx, upper_32_bits(value));
		armv8pmu_write_evcntr(idx - 1, lower_32_bits(value));
	} else {
		armv8pmu_write_evcntr(idx, value);
	}
}