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
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void kvmppc_load_guest_fp(struct kvm_vcpu *vcpu)
{
#ifdef CONFIG_PPC_FPU
	if (!(current->thread.regs->msr & MSR_FP)) {
		enable_kernel_fp();
		load_fp_state(&vcpu->arch.fp);
		disable_kernel_fp();
		current->thread.fp_save_area = &vcpu->arch.fp;
		current->thread.regs->msr |= MSR_FP;
	}
#endif
}