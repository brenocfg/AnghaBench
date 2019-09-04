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
struct hw_perf_event {int idx; int /*<<< orphan*/  event_base; int /*<<< orphan*/  config_base; scalar_t__ last_tag; } ;
struct perf_event {struct hw_perf_event hw; } ;
struct intel_uncore_box {scalar_t__* tags; } ;

/* Variables and functions */
 int /*<<< orphan*/  uncore_event_ctl (struct intel_uncore_box*,int) ; 
 int /*<<< orphan*/  uncore_fixed_ctl (struct intel_uncore_box*) ; 
 int /*<<< orphan*/  uncore_fixed_ctr (struct intel_uncore_box*) ; 
 int /*<<< orphan*/  uncore_perf_ctr (struct intel_uncore_box*,int) ; 
 scalar_t__ uncore_pmc_fixed (int) ; 

__attribute__((used)) static void uncore_assign_hw_event(struct intel_uncore_box *box,
				   struct perf_event *event, int idx)
{
	struct hw_perf_event *hwc = &event->hw;

	hwc->idx = idx;
	hwc->last_tag = ++box->tags[idx];

	if (uncore_pmc_fixed(hwc->idx)) {
		hwc->event_base = uncore_fixed_ctr(box);
		hwc->config_base = uncore_fixed_ctl(box);
		return;
	}

	hwc->config_base = uncore_event_ctl(box, hwc->idx);
	hwc->event_base  = uncore_perf_ctr(box, hwc->idx);
}