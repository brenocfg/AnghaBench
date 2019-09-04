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
struct sparc_stackf {unsigned long callers_pc; scalar_t__ fp; } ;
struct pt_regs {unsigned long tpc; unsigned long* u_regs; } ;
struct perf_callchain_entry_ctx {scalar_t__ nr; scalar_t__ max_stack; } ;

/* Variables and functions */
 unsigned long STACK_BIAS ; 
 size_t UREG_I6 ; 
 int /*<<< orphan*/  current_thread_info () ; 
 scalar_t__ kstack_is_trap_frame (int /*<<< orphan*/ ,struct pt_regs*) ; 
 int /*<<< orphan*/  kstack_valid (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  perf_callchain_store (struct perf_callchain_entry_ctx*,unsigned long) ; 
 int /*<<< orphan*/  stack_trace_flush () ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

void perf_callchain_kernel(struct perf_callchain_entry_ctx *entry,
			   struct pt_regs *regs)
{
	unsigned long ksp, fp;
#ifdef CONFIG_FUNCTION_GRAPH_TRACER
	int graph = 0;
#endif

	stack_trace_flush();

	perf_callchain_store(entry, regs->tpc);

	ksp = regs->u_regs[UREG_I6];
	fp = ksp + STACK_BIAS;
	do {
		struct sparc_stackf *sf;
		struct pt_regs *regs;
		unsigned long pc;

		if (!kstack_valid(current_thread_info(), fp))
			break;

		sf = (struct sparc_stackf *) fp;
		regs = (struct pt_regs *) (sf + 1);

		if (kstack_is_trap_frame(current_thread_info(), regs)) {
			if (user_mode(regs))
				break;
			pc = regs->tpc;
			fp = regs->u_regs[UREG_I6] + STACK_BIAS;
		} else {
			pc = sf->callers_pc;
			fp = (unsigned long)sf->fp + STACK_BIAS;
		}
		perf_callchain_store(entry, pc);
#ifdef CONFIG_FUNCTION_GRAPH_TRACER
		if ((pc + 8UL) == (unsigned long) &return_to_handler) {
			int index = current->curr_ret_stack;
			if (current->ret_stack && index >= graph) {
				pc = current->ret_stack[index - graph].ret;
				perf_callchain_store(entry, pc);
				graph++;
			}
		}
#endif
	} while (entry->nr < entry->max_stack);
}