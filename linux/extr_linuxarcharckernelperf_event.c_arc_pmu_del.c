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
struct TYPE_2__ {size_t idx; } ;
struct perf_event {TYPE_1__ hw; } ;
struct arc_pmu_cpu {scalar_t__* act_counter; int /*<<< orphan*/  used_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_EF_UPDATE ; 
 int /*<<< orphan*/  __clear_bit (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arc_pmu_cpu ; 
 int /*<<< orphan*/  arc_pmu_stop (struct perf_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_event_update_userpage (struct perf_event*) ; 
 struct arc_pmu_cpu* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void arc_pmu_del(struct perf_event *event, int flags)
{
	struct arc_pmu_cpu *pmu_cpu = this_cpu_ptr(&arc_pmu_cpu);

	arc_pmu_stop(event, PERF_EF_UPDATE);
	__clear_bit(event->hw.idx, pmu_cpu->used_mask);

	pmu_cpu->act_counter[event->hw.idx] = 0;

	perf_event_update_userpage(event);
}