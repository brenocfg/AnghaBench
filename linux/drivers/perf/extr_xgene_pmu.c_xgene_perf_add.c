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
struct xgene_pmu_dev {struct perf_event** pmu_counter_event; } ;
struct hw_perf_event {int state; size_t idx; } ;
struct perf_event {struct hw_perf_event hw; int /*<<< orphan*/  pmu; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  PERF_EF_RELOAD ; 
 int PERF_EF_START ; 
 int PERF_HES_STOPPED ; 
 int PERF_HES_UPTODATE ; 
 size_t get_next_avail_cntr (struct xgene_pmu_dev*) ; 
 struct xgene_pmu_dev* to_pmu_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgene_perf_start (struct perf_event*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xgene_perf_add(struct perf_event *event, int flags)
{
	struct xgene_pmu_dev *pmu_dev = to_pmu_dev(event->pmu);
	struct hw_perf_event *hw = &event->hw;

	hw->state = PERF_HES_UPTODATE | PERF_HES_STOPPED;

	/* Allocate an event counter */
	hw->idx = get_next_avail_cntr(pmu_dev);
	if (hw->idx < 0)
		return -EAGAIN;

	/* Update counter event pointer for Interrupt handler */
	pmu_dev->pmu_counter_event[hw->idx] = event;

	if (flags & PERF_EF_START)
		xgene_perf_start(event, PERF_EF_RELOAD);

	return 0;
}