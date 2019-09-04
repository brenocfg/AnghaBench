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

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_FRAME_POINTER ; 
 size_t FP_OFFSET ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int LOOP_TIMES ; 
 size_t LP_OFFSET ; 
 unsigned long TASK_SIZE ; 
 scalar_t__ __kernel_text_address (unsigned long) ; 
 unsigned long ftrace_graph_ret_addr (struct task_struct*,int*,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kstack_end (void*) ; 
 int /*<<< orphan*/  pr_emerg (char*) ; 
 int /*<<< orphan*/  print_ip_sym (unsigned long) ; 

__attribute__((used)) static void __dump(struct task_struct *tsk, unsigned long *base_reg)
{
	unsigned long ret_addr;
	int cnt = LOOP_TIMES, graph = 0;
	pr_emerg("Call Trace:\n");
	if (!IS_ENABLED(CONFIG_FRAME_POINTER)) {
		while (!kstack_end(base_reg)) {
			ret_addr = *base_reg++;
			if (__kernel_text_address(ret_addr)) {
				ret_addr = ftrace_graph_ret_addr(
						tsk, &graph, ret_addr, NULL);
				print_ip_sym(ret_addr);
			}
			if (--cnt < 0)
				break;
		}
	} else {
		while (!kstack_end((void *)base_reg) &&
		       !((unsigned long)base_reg & 0x3) &&
		       ((unsigned long)base_reg >= TASK_SIZE)) {
			unsigned long next_fp;
			ret_addr = base_reg[LP_OFFSET];
			next_fp = base_reg[FP_OFFSET];
			if (__kernel_text_address(ret_addr)) {

				ret_addr = ftrace_graph_ret_addr(
						tsk, &graph, ret_addr, NULL);
				print_ip_sym(ret_addr);
			}
			if (--cnt < 0)
				break;
			base_reg = (unsigned long *)next_fp;
		}
	}
	pr_emerg("\n");
}