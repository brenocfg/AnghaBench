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
struct tx2_uncore_pmu {int /*<<< orphan*/  (* init_cntr_base ) (struct perf_event*,struct tx2_uncore_pmu*) ;struct perf_event** events; } ;
struct hw_perf_event {size_t idx; int state; } ;
struct perf_event {int /*<<< orphan*/  pmu; struct hw_perf_event hw; } ;

/* Variables and functions */
 int EAGAIN ; 
 int PERF_EF_START ; 
 int PERF_HES_STOPPED ; 
 int PERF_HES_UPTODATE ; 
 size_t alloc_counter (struct tx2_uncore_pmu*) ; 
 struct tx2_uncore_pmu* pmu_to_tx2_pmu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct perf_event*,struct tx2_uncore_pmu*) ; 
 int /*<<< orphan*/  tx2_uncore_event_start (struct perf_event*,int) ; 

__attribute__((used)) static int tx2_uncore_event_add(struct perf_event *event, int flags)
{
	struct hw_perf_event *hwc = &event->hw;
	struct tx2_uncore_pmu *tx2_pmu;

	tx2_pmu = pmu_to_tx2_pmu(event->pmu);

	/* Allocate a free counter */
	hwc->idx  = alloc_counter(tx2_pmu);
	if (hwc->idx < 0)
		return -EAGAIN;

	tx2_pmu->events[hwc->idx] = event;
	/* set counter control and data registers base address */
	tx2_pmu->init_cntr_base(event, tx2_pmu);

	hwc->state = PERF_HES_UPTODATE | PERF_HES_STOPPED;
	if (flags & PERF_EF_START)
		tx2_uncore_event_start(event, flags);

	return 0;
}