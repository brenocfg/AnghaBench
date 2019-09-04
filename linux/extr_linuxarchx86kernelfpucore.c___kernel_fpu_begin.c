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
struct fpu {scalar_t__ initialized; } ;
struct TYPE_3__ {struct fpu fpu; } ;
struct TYPE_4__ {TYPE_1__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_FPU (int) ; 
 int /*<<< orphan*/  __cpu_invalidate_fpregs_state () ; 
 int /*<<< orphan*/  copy_fpregs_to_fpstate (struct fpu*) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  irq_fpu_usable () ; 
 int /*<<< orphan*/  kernel_fpu_disable () ; 

void __kernel_fpu_begin(void)
{
	struct fpu *fpu = &current->thread.fpu;

	WARN_ON_FPU(!irq_fpu_usable());

	kernel_fpu_disable();

	if (fpu->initialized) {
		/*
		 * Ignore return value -- we don't care if reg state
		 * is clobbered.
		 */
		copy_fpregs_to_fpstate(fpu);
	} else {
		__cpu_invalidate_fpregs_state();
	}
}