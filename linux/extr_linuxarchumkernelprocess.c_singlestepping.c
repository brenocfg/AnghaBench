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
struct task_struct {int ptrace; TYPE_1__ thread; } ;

/* Variables and functions */
 int PT_DTRACE ; 
 void* current ; 

int singlestepping(void * t)
{
	struct task_struct *task = t ? t : current;

	if (!(task->ptrace & PT_DTRACE))
		return 0;

	if (task->thread.singlestep_syscall)
		return 1;

	return 2;
}