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
struct perf_event {int dummy; } ;
struct event_constraint {int dummy; } ;
struct cpu_hw_events {int dummy; } ;

/* Variables and functions */
 struct event_constraint* intel_bts_constraints (struct perf_event*) ; 
 struct event_constraint* intel_pebs_constraints (struct perf_event*) ; 
 struct event_constraint* intel_shared_regs_constraints (struct cpu_hw_events*,struct perf_event*) ; 
 struct event_constraint* x86_get_event_constraints (struct cpu_hw_events*,int,struct perf_event*) ; 

__attribute__((used)) static struct event_constraint *
__intel_get_event_constraints(struct cpu_hw_events *cpuc, int idx,
			    struct perf_event *event)
{
	struct event_constraint *c;

	c = intel_bts_constraints(event);
	if (c)
		return c;

	c = intel_shared_regs_constraints(cpuc, event);
	if (c)
		return c;

	c = intel_pebs_constraints(event);
	if (c)
		return c;

	return x86_get_event_constraints(cpuc, idx, event);
}