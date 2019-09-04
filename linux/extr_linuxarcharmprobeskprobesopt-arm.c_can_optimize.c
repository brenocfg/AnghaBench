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
struct pt_regs {int dummy; } ;
struct TYPE_2__ {int stack_space; } ;
struct kprobe {TYPE_1__ ainsn; } ;

/* Variables and functions */

__attribute__((used)) static int can_optimize(struct kprobe *kp)
{
	if (kp->ainsn.stack_space < 0)
		return 0;
	/*
	 * 255 is the biggest imm can be used in 'sub r0, r0, #<imm>'.
	 * Number larger than 255 needs special encoding.
	 */
	if (kp->ainsn.stack_space > 255 - sizeof(struct pt_regs))
		return 0;
	return 1;
}