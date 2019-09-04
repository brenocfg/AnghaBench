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
struct fpu {int initialized; int /*<<< orphan*/  state; } ;
struct TYPE_3__ {struct fpu fpu; } ;
struct TYPE_4__ {TYPE_1__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_FPU (int) ; 
 int /*<<< orphan*/  __fpu_invalidate_fpregs_state (struct fpu*) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  fpstate_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_x86_fpu_activate_state (struct fpu*) ; 
 int /*<<< orphan*/  trace_x86_fpu_init_state (struct fpu*) ; 

void fpu__prepare_write(struct fpu *fpu)
{
	/*
	 * Only stopped child tasks can be used to modify the FPU
	 * state in the fpstate buffer:
	 */
	WARN_ON_FPU(fpu == &current->thread.fpu);

	if (fpu->initialized) {
		/* Invalidate any cached state: */
		__fpu_invalidate_fpregs_state(fpu);
	} else {
		fpstate_init(&fpu->state);
		trace_x86_fpu_init_state(fpu);

		trace_x86_fpu_activate_state(fpu);
		/* Safe to do for stopped child tasks: */
		fpu->initialized = 1;
	}
}