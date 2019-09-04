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
struct unwind_frame_info {int dummy; } ;
struct task_struct {int dummy; } ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_show_stack (struct unwind_frame_info*) ; 
 int /*<<< orphan*/  unwind_frame_init_task (struct unwind_frame_info*,struct task_struct*,struct pt_regs*) ; 

__attribute__((used)) static void parisc_show_stack(struct task_struct *task,
	struct pt_regs *regs)
{
	struct unwind_frame_info info;

	unwind_frame_init_task(&info, task, regs);

	do_show_stack(&info);
}