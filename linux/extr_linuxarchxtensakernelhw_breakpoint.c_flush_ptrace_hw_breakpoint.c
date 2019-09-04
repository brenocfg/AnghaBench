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
struct thread_struct {int /*<<< orphan*/ ** ptrace_wp; int /*<<< orphan*/ ** ptrace_bp; } ;
struct task_struct {struct thread_struct thread; } ;

/* Variables and functions */
 int XCHAL_NUM_DBREAK ; 
 int XCHAL_NUM_IBREAK ; 
 int /*<<< orphan*/  unregister_hw_breakpoint (int /*<<< orphan*/ *) ; 

void flush_ptrace_hw_breakpoint(struct task_struct *tsk)
{
	int i;
	struct thread_struct *t = &tsk->thread;

	for (i = 0; i < XCHAL_NUM_IBREAK; ++i) {
		if (t->ptrace_bp[i]) {
			unregister_hw_breakpoint(t->ptrace_bp[i]);
			t->ptrace_bp[i] = NULL;
		}
	}
	for (i = 0; i < XCHAL_NUM_DBREAK; ++i) {
		if (t->ptrace_wp[i]) {
			unregister_hw_breakpoint(t->ptrace_wp[i]);
			t->ptrace_wp[i] = NULL;
		}
	}
}