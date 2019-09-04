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
 int /*<<< orphan*/  WARN_ON_FPU (int) ; 
 int /*<<< orphan*/  copy_fpregs_to_fpstate (struct fpu*) ; 
 int /*<<< orphan*/  copy_kernel_to_fpregs (int /*<<< orphan*/ *) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  trace_x86_fpu_after_save (struct fpu*) ; 
 int /*<<< orphan*/  trace_x86_fpu_before_save (struct fpu*) ; 

void fpu__save(struct fpu *fpu)
{
	WARN_ON_FPU(fpu != &current->thread.fpu);

	preempt_disable();
	trace_x86_fpu_before_save(fpu);
	if (fpu->initialized) {
		if (!copy_fpregs_to_fpstate(fpu)) {
			copy_kernel_to_fpregs(&fpu->state);
		}
	}
	trace_x86_fpu_after_save(fpu);
	preempt_enable();
}