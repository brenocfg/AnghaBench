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
struct stack_trace {int dummy; } ;
struct pt_regs {scalar_t__ sp; } ;

/* Variables and functions */
 int /*<<< orphan*/  save_stack_address_nosched ; 
 int /*<<< orphan*/  unwind_stack (struct stack_trace*,unsigned long*,int /*<<< orphan*/ ) ; 

void
save_stack_trace_regs(struct pt_regs *regs, struct stack_trace *trace)
{
	unwind_stack(trace, (unsigned long *) regs->sp,
		     save_stack_address_nosched);
}