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
struct stack_trace {int dummy; } ;
struct pt_regs {int /*<<< orphan*/  r15; int /*<<< orphan*/  r1; int /*<<< orphan*/  pc; } ;

/* Variables and functions */
 int /*<<< orphan*/  microblaze_unwind_inner (struct task_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct stack_trace*) ; 

__attribute__((used)) static inline void unwind_trap(struct task_struct *task, unsigned long pc,
				unsigned long fp, struct stack_trace *trace)
{
	const struct pt_regs *regs = (const struct pt_regs *) fp;
	microblaze_unwind_inner(task, regs->pc, regs->r1, regs->r15, trace);
}