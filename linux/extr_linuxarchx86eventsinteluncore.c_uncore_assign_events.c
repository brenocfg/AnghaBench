#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct intel_uncore_box {TYPE_1__** event_list; struct event_constraint** event_constraint; } ;
struct hw_perf_event {int idx; } ;
struct event_constraint {unsigned long* idxmsk; int /*<<< orphan*/  weight; } ;
struct TYPE_3__ {struct hw_perf_event hw; } ;

/* Variables and functions */
 int BITS_TO_LONGS (int) ; 
 int EINVAL ; 
 int UNCORE_PMC_IDX_MAX ; 
 int /*<<< orphan*/  __set_bit (int,unsigned long*) ; 
 int /*<<< orphan*/  bitmap_zero (unsigned long*,int) ; 
 int max (int,int /*<<< orphan*/ ) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int perf_assign_events (struct event_constraint**,int,int,int,int,int*) ; 
 scalar_t__ test_bit (int,unsigned long*) ; 
 struct event_constraint* uncore_get_event_constraint (struct intel_uncore_box*,TYPE_1__*) ; 
 int /*<<< orphan*/  uncore_put_event_constraint (struct intel_uncore_box*,TYPE_1__*) ; 

__attribute__((used)) static int uncore_assign_events(struct intel_uncore_box *box, int assign[], int n)
{
	unsigned long used_mask[BITS_TO_LONGS(UNCORE_PMC_IDX_MAX)];
	struct event_constraint *c;
	int i, wmin, wmax, ret = 0;
	struct hw_perf_event *hwc;

	bitmap_zero(used_mask, UNCORE_PMC_IDX_MAX);

	for (i = 0, wmin = UNCORE_PMC_IDX_MAX, wmax = 0; i < n; i++) {
		c = uncore_get_event_constraint(box, box->event_list[i]);
		box->event_constraint[i] = c;
		wmin = min(wmin, c->weight);
		wmax = max(wmax, c->weight);
	}

	/* fastpath, try to reuse previous register */
	for (i = 0; i < n; i++) {
		hwc = &box->event_list[i]->hw;
		c = box->event_constraint[i];

		/* never assigned */
		if (hwc->idx == -1)
			break;

		/* constraint still honored */
		if (!test_bit(hwc->idx, c->idxmsk))
			break;

		/* not already used */
		if (test_bit(hwc->idx, used_mask))
			break;

		__set_bit(hwc->idx, used_mask);
		if (assign)
			assign[i] = hwc->idx;
	}
	/* slow path */
	if (i != n)
		ret = perf_assign_events(box->event_constraint, n,
					 wmin, wmax, n, assign);

	if (!assign || ret) {
		for (i = 0; i < n; i++)
			uncore_put_event_constraint(box, box->event_list[i]);
	}
	return ret ? -EINVAL : 0;
}