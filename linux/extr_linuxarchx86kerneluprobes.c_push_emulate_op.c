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
struct pt_regs {int /*<<< orphan*/  ip; } ;
struct TYPE_2__ {int reg_offset; scalar_t__ ilen; } ;
struct arch_uprobe {TYPE_1__ push; } ;

/* Variables and functions */
 scalar_t__ emulate_push_stack (struct pt_regs*,unsigned long) ; 

__attribute__((used)) static bool push_emulate_op(struct arch_uprobe *auprobe, struct pt_regs *regs)
{
	unsigned long *src_ptr = (void *)regs + auprobe->push.reg_offset;

	if (emulate_push_stack(regs, *src_ptr))
		return false;
	regs->ip += auprobe->push.ilen;
	return true;
}