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
struct fpu {int /*<<< orphan*/  state; scalar_t__ initialized; } ;
struct TYPE_3__ {struct fpu fpu; } ;
struct TYPE_4__ {TYPE_1__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  copy_kernel_to_fpregs (int /*<<< orphan*/ *) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  kernel_fpu_enable () ; 

void __kernel_fpu_end(void)
{
	struct fpu *fpu = &current->thread.fpu;

	if (fpu->initialized)
		copy_kernel_to_fpregs(&fpu->state);

	kernel_fpu_enable();
}