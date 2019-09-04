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
struct xtensa_pmu_events {int /*<<< orphan*/  used_mask; } ;
struct TYPE_2__ {int /*<<< orphan*/  idx; } ;
struct perf_event {TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_EF_UPDATE ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_event_update_userpage (struct perf_event*) ; 
 struct xtensa_pmu_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xtensa_pmu_events ; 
 int /*<<< orphan*/  xtensa_pmu_stop (struct perf_event*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xtensa_pmu_del(struct perf_event *event, int flags)
{
	struct xtensa_pmu_events *ev = this_cpu_ptr(&xtensa_pmu_events);

	xtensa_pmu_stop(event, PERF_EF_UPDATE);
	__clear_bit(event->hw.idx, ev->used_mask);
	perf_event_update_userpage(event);
}