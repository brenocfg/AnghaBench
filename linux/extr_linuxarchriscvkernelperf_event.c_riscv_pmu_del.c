#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hw_perf_event {size_t idx; } ;
struct perf_event {struct hw_perf_event hw; } ;
struct cpu_hw_events {int /*<<< orphan*/  n_events; int /*<<< orphan*/ ** events; } ;
struct TYPE_4__ {TYPE_1__* pmu; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* stop ) (struct perf_event*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_EF_UPDATE ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 int /*<<< orphan*/  perf_event_update_userpage (struct perf_event*) ; 
 TYPE_2__* riscv_pmu ; 
 int /*<<< orphan*/  stub1 (struct perf_event*,int /*<<< orphan*/ ) ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void riscv_pmu_del(struct perf_event *event, int flags)
{
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	struct hw_perf_event *hwc = &event->hw;

	cpuc->events[hwc->idx] = NULL;
	cpuc->n_events--;
	riscv_pmu->pmu->stop(event, PERF_EF_UPDATE);
	perf_event_update_userpage(event);
}