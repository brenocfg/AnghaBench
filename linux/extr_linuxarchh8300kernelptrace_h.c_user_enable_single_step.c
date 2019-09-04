#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned short* addr; unsigned short inst; } ;
struct TYPE_4__ {TYPE_1__ breakinfo; } ;
struct task_struct {TYPE_2__ thread; } ;

/* Variables and functions */
 unsigned short BREAKINST ; 
 int /*<<< orphan*/  PT_PC ; 
 scalar_t__ h8300_get_reg (struct task_struct*,int /*<<< orphan*/ ) ; 
 unsigned short* nextpc (struct task_struct*,unsigned short*) ; 

void user_enable_single_step(struct task_struct *child)
{
	unsigned short *next;

	next = nextpc(child, (unsigned short *)h8300_get_reg(child, PT_PC));
	child->thread.breakinfo.addr = next;
	child->thread.breakinfo.inst = *next;
	*next = BREAKINST;
}