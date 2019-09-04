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

__attribute__((used)) static inline void kvmppc_load_guest_altivec(struct kvm_vcpu *vcpu)
{
#ifdef CONFIG_ALTIVEC
	if (cpu_has_feature(CPU_FTR_ALTIVEC)) {
		if (!(current->thread.regs->msr & MSR_VEC)) {
			enable_kernel_altivec();
			load_vr_state(&vcpu->arch.vr);
			disable_kernel_altivec();
			current->thread.vr_save_area = &vcpu->arch.vr;
			current->thread.regs->msr |= MSR_VEC;
		}
	}
#endif
}