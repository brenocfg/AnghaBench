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
typedef  int u64 ;
struct TYPE_2__ {int idx; int /*<<< orphan*/  prev_count; } ;
struct perf_event {TYPE_1__ hw; } ;

/* Variables and functions */
 int DSU_PMU_COUNTER_MASK (int) ; 
 int /*<<< orphan*/  dsu_pmu_write_counter (struct perf_event*,int) ; 
 int /*<<< orphan*/  local64_set (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void dsu_pmu_set_event_period(struct perf_event *event)
{
	int idx = event->hw.idx;
	u64 val = DSU_PMU_COUNTER_MASK(idx) >> 1;

	local64_set(&event->hw.prev_count, val);
	dsu_pmu_write_counter(event, val);
}