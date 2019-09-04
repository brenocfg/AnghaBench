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
struct hw_perf_event {size_t idx; size_t config; int state; } ;
struct perf_event {struct hw_perf_event hw; } ;
struct cpu_hw_events {scalar_t__ n_events; struct perf_event** events; } ;
struct TYPE_4__ {scalar_t__ num_counters; TYPE_1__* pmu; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* start ) (struct perf_event*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  PERF_EF_RELOAD ; 
 int PERF_EF_START ; 
 int PERF_HES_STOPPED ; 
 int PERF_HES_UPTODATE ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 TYPE_2__* riscv_pmu ; 
 int /*<<< orphan*/  stub1 (struct perf_event*,int /*<<< orphan*/ ) ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int riscv_pmu_add(struct perf_event *event, int flags)
{
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	struct hw_perf_event *hwc = &event->hw;

	if (cpuc->n_events == riscv_pmu->num_counters)
		return -ENOSPC;

	/*
	 * We don't have general conunters, so no binding-event-to-counter
	 * process here.
	 *
	 * Indexing using hwc->config generally not works, since config may
	 * contain extra information, but here the only info we have in
	 * hwc->config is the event index.
	 */
	hwc->idx = hwc->config;
	cpuc->events[hwc->idx] = event;
	cpuc->n_events++;

	hwc->state = PERF_HES_UPTODATE | PERF_HES_STOPPED;

	if (flags & PERF_EF_START)
		riscv_pmu->pmu->start(event, PERF_EF_RELOAD);

	return 0;
}