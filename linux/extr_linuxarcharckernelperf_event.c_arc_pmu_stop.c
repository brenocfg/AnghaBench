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
struct hw_perf_event {int idx; int state; } ;
struct perf_event {struct hw_perf_event hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARC_REG_PCT_CONFIG ; 
 int /*<<< orphan*/  ARC_REG_PCT_INDEX ; 
 int /*<<< orphan*/  ARC_REG_PCT_INT_ACT ; 
 int /*<<< orphan*/  ARC_REG_PCT_INT_CTRL ; 
 int PERF_EF_UPDATE ; 
 int PERF_HES_STOPPED ; 
 int PERF_HES_UPTODATE ; 
 int /*<<< orphan*/  arc_perf_event_update (struct perf_event*,struct hw_perf_event*,int) ; 
 scalar_t__ is_sampling_event (struct perf_event*) ; 
 int read_aux_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_aux_reg (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void arc_pmu_stop(struct perf_event *event, int flags)
{
	struct hw_perf_event *hwc = &event->hw;
	int idx = hwc->idx;

	/* Disable interrupt for this counter */
	if (is_sampling_event(event)) {
		/*
		 * Reset interrupt flag by writing of 1. This is required
		 * to make sure pending interrupt was not left.
		 */
		write_aux_reg(ARC_REG_PCT_INT_ACT, 1 << idx);
		write_aux_reg(ARC_REG_PCT_INT_CTRL,
			      read_aux_reg(ARC_REG_PCT_INT_CTRL) & ~(1 << idx));
	}

	if (!(event->hw.state & PERF_HES_STOPPED)) {
		/* stop ARC pmu here */
		write_aux_reg(ARC_REG_PCT_INDEX, idx);

		/* condition code #0 is always "never" */
		write_aux_reg(ARC_REG_PCT_CONFIG, 0);

		event->hw.state |= PERF_HES_STOPPED;
	}

	if ((flags & PERF_EF_UPDATE) &&
	    !(event->hw.state & PERF_HES_UPTODATE)) {
		arc_perf_event_update(event, &event->hw, idx);
		event->hw.state |= PERF_HES_UPTODATE;
	}
}