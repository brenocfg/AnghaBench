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
struct stack_trace {scalar_t__ nr_entries; scalar_t__ max_entries; int /*<<< orphan*/ * entries; } ;
struct TYPE_2__ {scalar_t__ mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  ULONG_MAX ; 
 int /*<<< orphan*/  __save_stack_trace_user (struct stack_trace*) ; 
 TYPE_1__* current ; 

void save_stack_trace_user(struct stack_trace *trace)
{
	/*
	 * Trace user stack if we are not a kernel thread
	 */
	if (current->mm) {
		__save_stack_trace_user(trace);
	}
	if (trace->nr_entries < trace->max_entries)
		trace->entries[trace->nr_entries++] = ULONG_MAX;
}