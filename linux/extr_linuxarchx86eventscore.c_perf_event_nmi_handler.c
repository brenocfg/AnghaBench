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
typedef  scalar_t__ u64 ;
struct pt_regs {int dummy; } ;
struct TYPE_2__ {int (* handle_irq ) (struct pt_regs*) ;} ;

/* Variables and functions */
 int NMI_DONE ; 
 int /*<<< orphan*/  active_events ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_sample_event_took (scalar_t__) ; 
 scalar_t__ sched_clock () ; 
 int stub1 (struct pt_regs*) ; 
 TYPE_1__ x86_pmu ; 

__attribute__((used)) static int
perf_event_nmi_handler(unsigned int cmd, struct pt_regs *regs)
{
	u64 start_clock;
	u64 finish_clock;
	int ret;

	/*
	 * All PMUs/events that share this PMI handler should make sure to
	 * increment active_events for their events.
	 */
	if (!atomic_read(&active_events))
		return NMI_DONE;

	start_clock = sched_clock();
	ret = x86_pmu.handle_irq(regs);
	finish_clock = sched_clock();

	perf_sample_event_took(finish_clock - start_clock);

	return ret;
}