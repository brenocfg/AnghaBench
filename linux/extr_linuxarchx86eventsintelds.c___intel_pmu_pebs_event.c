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
struct pt_regs {int dummy; } ;
struct perf_sample_data {int dummy; } ;
struct hw_perf_event {int flags; } ;
struct perf_event {struct hw_perf_event hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  pebs_record_size; } ;

/* Variables and functions */
 int PERF_X86_EVENT_AUTO_RELOAD ; 
 void* get_next_pebs_record_by_bit (void*,void*,int) ; 
 int /*<<< orphan*/  intel_pmu_save_and_restart (struct perf_event*) ; 
 int /*<<< orphan*/  intel_pmu_save_and_restart_reload (struct perf_event*,int) ; 
 int /*<<< orphan*/  perf_event_output (struct perf_event*,struct perf_sample_data*,struct pt_regs*) ; 
 scalar_t__ perf_event_overflow (struct perf_event*,struct perf_sample_data*,struct pt_regs*) ; 
 int /*<<< orphan*/  setup_pebs_sample_data (struct perf_event*,struct pt_regs*,void*,struct perf_sample_data*,struct pt_regs*) ; 
 TYPE_1__ x86_pmu ; 
 int /*<<< orphan*/  x86_pmu_stop (struct perf_event*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __intel_pmu_pebs_event(struct perf_event *event,
				   struct pt_regs *iregs,
				   void *base, void *top,
				   int bit, int count)
{
	struct hw_perf_event *hwc = &event->hw;
	struct perf_sample_data data;
	struct pt_regs regs;
	void *at = get_next_pebs_record_by_bit(base, top, bit);

	if (hwc->flags & PERF_X86_EVENT_AUTO_RELOAD) {
		/*
		 * Now, auto-reload is only enabled in fixed period mode.
		 * The reload value is always hwc->sample_period.
		 * May need to change it, if auto-reload is enabled in
		 * freq mode later.
		 */
		intel_pmu_save_and_restart_reload(event, count);
	} else if (!intel_pmu_save_and_restart(event))
		return;

	while (count > 1) {
		setup_pebs_sample_data(event, iregs, at, &data, &regs);
		perf_event_output(event, &data, &regs);
		at += x86_pmu.pebs_record_size;
		at = get_next_pebs_record_by_bit(at, top, bit);
		count--;
	}

	setup_pebs_sample_data(event, iregs, at, &data, &regs);

	/*
	 * All but the last records are processed.
	 * The last one is left to be able to call the overflow handler.
	 */
	if (perf_event_overflow(event, &data, &regs)) {
		x86_pmu_stop(event, 0);
		return;
	}

}