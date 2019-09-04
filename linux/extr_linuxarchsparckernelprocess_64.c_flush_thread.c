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
struct thread_info {scalar_t__* fpsaved; TYPE_1__* task; } ;
struct mm_struct {int dummy; } ;
struct TYPE_2__ {struct mm_struct* mm; } ;

/* Variables and functions */
 struct thread_info* current_thread_info () ; 
 int /*<<< orphan*/  set_thread_wsaved (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsb_context_switch (struct mm_struct*) ; 

void flush_thread(void)
{
	struct thread_info *t = current_thread_info();
	struct mm_struct *mm;

	mm = t->task->mm;
	if (mm)
		tsb_context_switch(mm);

	set_thread_wsaved(0);

	/* Clear FPU register state. */
	t->fpsaved[0] = 0;
}