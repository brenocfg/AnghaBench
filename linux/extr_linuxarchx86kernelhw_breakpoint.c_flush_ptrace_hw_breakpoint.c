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
struct thread_struct {scalar_t__ ptrace_dr7; scalar_t__ debugreg6; int /*<<< orphan*/ ** ptrace_bps; } ;
struct task_struct {struct thread_struct thread; } ;

/* Variables and functions */
 int HBP_NUM ; 
 int /*<<< orphan*/  unregister_hw_breakpoint (int /*<<< orphan*/ *) ; 

void flush_ptrace_hw_breakpoint(struct task_struct *tsk)
{
	int i;
	struct thread_struct *t = &tsk->thread;

	for (i = 0; i < HBP_NUM; i++) {
		unregister_hw_breakpoint(t->ptrace_bps[i]);
		t->ptrace_bps[i] = NULL;
	}

	t->debugreg6 = 0;
	t->ptrace_dr7 = 0;
}