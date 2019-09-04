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
struct thread_info {int dummy; } ;
struct task_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIF_SINGLESTEP ; 
 int /*<<< orphan*/  set_regs_spsr_ss (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_pt_regs (struct task_struct*) ; 
 struct thread_info* task_thread_info (struct task_struct*) ; 
 int /*<<< orphan*/  test_and_set_ti_thread_flag (struct thread_info*,int /*<<< orphan*/ ) ; 

void user_enable_single_step(struct task_struct *task)
{
	struct thread_info *ti = task_thread_info(task);

	if (!test_and_set_ti_thread_flag(ti, TIF_SINGLESTEP))
		set_regs_spsr_ss(task_pt_regs(task));
}