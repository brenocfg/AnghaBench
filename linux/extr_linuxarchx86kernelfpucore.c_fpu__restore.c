#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct fpu {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  copy_kernel_to_fpregs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fpregs_activate (struct fpu*) ; 
 int /*<<< orphan*/  fpu__initialize (struct fpu*) ; 
 int /*<<< orphan*/  kernel_fpu_disable () ; 
 int /*<<< orphan*/  kernel_fpu_enable () ; 
 int /*<<< orphan*/  trace_x86_fpu_after_restore (struct fpu*) ; 
 int /*<<< orphan*/  trace_x86_fpu_before_restore (struct fpu*) ; 

void fpu__restore(struct fpu *fpu)
{
	fpu__initialize(fpu);

	/* Avoid __kernel_fpu_begin() right after fpregs_activate() */
	kernel_fpu_disable();
	trace_x86_fpu_before_restore(fpu);
	fpregs_activate(fpu);
	copy_kernel_to_fpregs(&fpu->state);
	trace_x86_fpu_after_restore(fpu);
	kernel_fpu_enable();
}