#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  fpu; int /*<<< orphan*/  tls_array; } ;
struct task_struct {TYPE_1__ thread; } ;

/* Variables and functions */
 struct task_struct* current ; 
 int /*<<< orphan*/  flush_ptrace_hw_breakpoint (struct task_struct*) ; 
 int /*<<< orphan*/  fpu__clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void flush_thread(void)
{
	struct task_struct *tsk = current;

	flush_ptrace_hw_breakpoint(tsk);
	memset(tsk->thread.tls_array, 0, sizeof(tsk->thread.tls_array));

	fpu__clear(&tsk->thread.fpu);
}