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
struct cpu_context {unsigned long r1; int /*<<< orphan*/  r15; } ;
struct thread_info {struct cpu_context cpu_context; } ;
struct task_struct {scalar_t__ stack; } ;
struct stack_trace {int dummy; } ;
struct pt_regs {unsigned long pc; unsigned long r1; int /*<<< orphan*/  r15; } ;

/* Variables and functions */
 int /*<<< orphan*/  _switch_to ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  microblaze_unwind_inner (struct task_struct*,unsigned long,unsigned long,int /*<<< orphan*/ ,struct stack_trace*) ; 
 struct pt_regs* task_pt_regs (struct task_struct*) ; 

void microblaze_unwind(struct task_struct *task, struct stack_trace *trace)
{
	if (task) {
		if (task == current) {
			const struct pt_regs *regs = task_pt_regs(task);
			microblaze_unwind_inner(task, regs->pc, regs->r1,
						regs->r15, trace);
		} else {
			struct thread_info *thread_info =
				(struct thread_info *)(task->stack);
			const struct cpu_context *cpu_context =
				&thread_info->cpu_context;

			microblaze_unwind_inner(task,
						(unsigned long) &_switch_to,
						cpu_context->r1,
						cpu_context->r15, trace);
		}
	} else {
		unsigned long pc, fp;

		__asm__ __volatile__ ("or %0, r1, r0" : "=r" (fp));

		__asm__ __volatile__ (
			"brlid %0, 0f;"
			"nop;"
			"0:"
			: "=r" (pc)
		);

		/* Since we are not a leaf function, use leaf_return = 0 */
		microblaze_unwind_inner(current, pc, fp, 0, trace);
	}
}