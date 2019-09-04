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
struct stack_trace {int skip; } ;

/* Variables and functions */
 int /*<<< orphan*/  microblaze_unwind (int /*<<< orphan*/ *,struct stack_trace*) ; 

void save_stack_trace(struct stack_trace *trace)
{
	/* Exclude our helper functions from the trace*/
	trace->skip += 2;
	microblaze_unwind(NULL, trace);
}