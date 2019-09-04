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
struct user_regset {int n; } ;
struct fpu {scalar_t__ initialized; } ;
struct TYPE_2__ {struct fpu fpu; } ;
struct task_struct {TYPE_1__ thread; } ;

/* Variables and functions */

int regset_fpregs_active(struct task_struct *target, const struct user_regset *regset)
{
	struct fpu *target_fpu = &target->thread.fpu;

	return target_fpu->initialized ? regset->n : 0;
}