#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  xsave; } ;
struct fpu {int last_cpu; TYPE_2__ state; int /*<<< orphan*/  initialized; } ;
struct TYPE_6__ {struct fpu fpu; } ;
struct TYPE_8__ {TYPE_1__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_FPU (int) ; 
 int /*<<< orphan*/  X86_FEATURE_FPU ; 
 int /*<<< orphan*/  copy_fpregs_to_fpstate (struct fpu*) ; 
 int /*<<< orphan*/  copy_kernel_to_fpregs (TYPE_2__*) ; 
 TYPE_4__* current ; 
 int /*<<< orphan*/  fpu_kernel_xstate_size ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  static_cpu_has (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_x86_fpu_copy_dst (struct fpu*) ; 
 int /*<<< orphan*/  trace_x86_fpu_copy_src (struct fpu*) ; 

int fpu__copy(struct fpu *dst_fpu, struct fpu *src_fpu)
{
	dst_fpu->last_cpu = -1;

	if (!src_fpu->initialized || !static_cpu_has(X86_FEATURE_FPU))
		return 0;

	WARN_ON_FPU(src_fpu != &current->thread.fpu);

	/*
	 * Don't let 'init optimized' areas of the XSAVE area
	 * leak into the child task:
	 */
	memset(&dst_fpu->state.xsave, 0, fpu_kernel_xstate_size);

	/*
	 * Save current FPU registers directly into the child
	 * FPU context, without any memory-to-memory copying.
	 *
	 * ( The function 'fails' in the FNSAVE case, which destroys
	 *   register contents so we have to copy them back. )
	 */
	if (!copy_fpregs_to_fpstate(dst_fpu)) {
		memcpy(&src_fpu->state, &dst_fpu->state, fpu_kernel_xstate_size);
		copy_kernel_to_fpregs(&src_fpu->state);
	}

	trace_x86_fpu_copy_src(src_fpu);
	trace_x86_fpu_copy_dst(dst_fpu);

	return 0;
}