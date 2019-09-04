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
struct stack_trace {scalar_t__ skip; scalar_t__ nr_entries; scalar_t__ max_entries; unsigned long* entries; } ;

/* Variables and functions */
 scalar_t__ in_sched_functions (unsigned long) ; 

__attribute__((used)) static int __save_address(void *data, unsigned long address, int nosched)
{
	struct stack_trace *trace = data;

	if (nosched && in_sched_functions(address))
		return 0;
	if (trace->skip > 0) {
		trace->skip--;
		return 0;
	}
	if (trace->nr_entries < trace->max_entries) {
		trace->entries[trace->nr_entries++] = address;
		return 0;
	}
	return 1;
}