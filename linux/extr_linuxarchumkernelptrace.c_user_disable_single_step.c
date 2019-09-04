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
struct TYPE_2__ {scalar_t__ singlestep_syscall; } ;
struct task_struct {TYPE_1__ thread; int /*<<< orphan*/  ptrace; } ;

/* Variables and functions */
 int /*<<< orphan*/  PT_DTRACE ; 

void user_disable_single_step(struct task_struct *child)
{
	child->ptrace &= ~PT_DTRACE;
	child->thread.singlestep_syscall = 0;

#ifdef SUBARCH_SET_SINGLESTEPPING
	SUBARCH_SET_SINGLESTEPPING(child, 0);
#endif
}