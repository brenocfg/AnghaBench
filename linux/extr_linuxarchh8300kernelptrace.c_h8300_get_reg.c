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
struct TYPE_2__ {scalar_t__ esp0; int /*<<< orphan*/  usp; } ;
struct task_struct {TYPE_1__ thread; } ;

/* Variables and functions */
#define  PT_CCR 130 
#define  PT_EXR 129 
#define  PT_USP 128 
 scalar_t__* register_offset ; 

long h8300_get_reg(struct task_struct *task, int regno)
{
	switch (regno) {
	case PT_USP:
		return task->thread.usp + sizeof(long)*2;
	case PT_CCR:
	case PT_EXR:
	    return *(unsigned short *)(task->thread.esp0 +
				       register_offset[regno]);
	default:
	    return *(unsigned long *)(task->thread.esp0 +
				      register_offset[regno]);
	}
}