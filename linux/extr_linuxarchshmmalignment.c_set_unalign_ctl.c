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
struct TYPE_2__ {unsigned int flags; } ;
struct task_struct {TYPE_1__ thread; } ;

/* Variables and functions */
 unsigned int SH_THREAD_UAC_MASK ; 

int set_unalign_ctl(struct task_struct *tsk, unsigned int val)
{
	tsk->thread.flags = (tsk->thread.flags & ~SH_THREAD_UAC_MASK) |
			    (val & SH_THREAD_UAC_MASK);
	return 0;
}