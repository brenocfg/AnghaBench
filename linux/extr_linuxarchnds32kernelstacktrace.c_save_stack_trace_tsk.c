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
struct task_struct {int dummy; } ;
struct stack_trace {int skip; unsigned long* entries; scalar_t__ nr_entries; scalar_t__ max_entries; } ;

/* Variables and functions */
 size_t FP_OFFSET ; 
 size_t LP_OFFSET ; 
 scalar_t__ TASK_SIZE ; 
 int /*<<< orphan*/  __kernel_text_address (unsigned long) ; 
 struct task_struct* current ; 
 unsigned long ftrace_graph_ret_addr (struct task_struct*,int*,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  in_sched_functions (unsigned long) ; 
 int /*<<< orphan*/  kstack_end (unsigned long*) ; 
 scalar_t__ thread_saved_fp (struct task_struct*) ; 

void save_stack_trace_tsk(struct task_struct *tsk, struct stack_trace *trace)
{
	unsigned long *fpn;
	int skip = trace->skip;
	int savesched;
	int graph_idx = 0;

	if (tsk == current) {
		__asm__ __volatile__("\tori\t%0, $fp, #0\n":"=r"(fpn));
		savesched = 1;
	} else {
		fpn = (unsigned long *)thread_saved_fp(tsk);
		savesched = 0;
	}

	while (!kstack_end(fpn) && !((unsigned long)fpn & 0x3)
	       && (fpn >= (unsigned long *)TASK_SIZE)) {
		unsigned long lpp, fpp;

		lpp = fpn[LP_OFFSET];
		fpp = fpn[FP_OFFSET];
		if (!__kernel_text_address(lpp))
			break;
		else
			lpp = ftrace_graph_ret_addr(tsk, &graph_idx, lpp, NULL);

		if (savesched || !in_sched_functions(lpp)) {
			if (skip) {
				skip--;
			} else {
				trace->entries[trace->nr_entries++] = lpp;
				if (trace->nr_entries >= trace->max_entries)
					break;
			}
		}
		fpn = (unsigned long *)fpp;
	}
}