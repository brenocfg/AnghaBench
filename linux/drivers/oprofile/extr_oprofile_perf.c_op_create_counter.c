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
struct perf_event {scalar_t__ state; } ;
struct TYPE_2__ {int /*<<< orphan*/  attr; int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ IS_ERR (struct perf_event*) ; 
 scalar_t__ PERF_EVENT_STATE_ACTIVE ; 
 int PTR_ERR (struct perf_event*) ; 
 TYPE_1__* counter_config ; 
 int /*<<< orphan*/  op_overflow_handler ; 
 struct perf_event** per_cpu (int /*<<< orphan*/ ,int) ; 
 struct perf_event* perf_event_create_kernel_counter (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_event_release_kernel (struct perf_event*) ; 
 int /*<<< orphan*/  perf_events ; 
 int /*<<< orphan*/  pr_warning (char*,int,int) ; 

__attribute__((used)) static int op_create_counter(int cpu, int event)
{
	struct perf_event *pevent;

	if (!counter_config[event].enabled || per_cpu(perf_events, cpu)[event])
		return 0;

	pevent = perf_event_create_kernel_counter(&counter_config[event].attr,
						  cpu, NULL,
						  op_overflow_handler, NULL);

	if (IS_ERR(pevent))
		return PTR_ERR(pevent);

	if (pevent->state != PERF_EVENT_STATE_ACTIVE) {
		perf_event_release_kernel(pevent);
		pr_warning("oprofile: failed to enable event %d "
				"on CPU %d\n", event, cpu);
		return -EBUSY;
	}

	per_cpu(perf_events, cpu)[event] = pevent;

	return 0;
}