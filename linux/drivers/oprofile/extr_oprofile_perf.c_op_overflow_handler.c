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
typedef  int /*<<< orphan*/  u32 ;
struct pt_regs {int dummy; } ;
struct perf_sample_data {int dummy; } ;
struct perf_event {int dummy; } ;

/* Variables and functions */
 int num_counters ; 
 int /*<<< orphan*/  oprofile_add_sample (struct pt_regs*,int) ; 
 struct perf_event** per_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_events ; 
 int /*<<< orphan*/  pr_warning (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static void op_overflow_handler(struct perf_event *event,
			struct perf_sample_data *data, struct pt_regs *regs)
{
	int id;
	u32 cpu = smp_processor_id();

	for (id = 0; id < num_counters; ++id)
		if (per_cpu(perf_events, cpu)[id] == event)
			break;

	if (id != num_counters)
		oprofile_add_sample(regs, id);
	else
		pr_warning("oprofile: ignoring spurious overflow "
				"on cpu %u\n", cpu);
}