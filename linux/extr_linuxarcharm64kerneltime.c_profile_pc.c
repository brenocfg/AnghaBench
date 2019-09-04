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
struct stackframe {unsigned long pc; int /*<<< orphan*/  fp; } ;
struct pt_regs {unsigned long pc; int /*<<< orphan*/ * regs; } ;

/* Variables and functions */
 scalar_t__ in_lock_functions (unsigned long) ; 
 int unwind_frame (int /*<<< orphan*/ *,struct stackframe*) ; 

unsigned long profile_pc(struct pt_regs *regs)
{
	struct stackframe frame;

	if (!in_lock_functions(regs->pc))
		return regs->pc;

	frame.fp = regs->regs[29];
	frame.pc = regs->pc;
#ifdef CONFIG_FUNCTION_GRAPH_TRACER
	frame.graph = current->curr_ret_stack;
#endif
	do {
		int ret = unwind_frame(NULL, &frame);
		if (ret < 0)
			return 0;
	} while (in_lock_functions(frame.pc));

	return frame.pc;
}