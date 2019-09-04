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
struct TYPE_2__ {int flags; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPACR_EL1 ; 
 int /*<<< orphan*/  CPACR_EL1_ZEN_EL0EN ; 
 int KVM_ARM64_FP_ENABLED ; 
 int KVM_ARM64_HOST_SVE_ENABLED ; 
 int KVM_ARM64_HOST_SVE_IN_USE ; 
 int /*<<< orphan*/  TIF_SVE ; 
 int /*<<< orphan*/  fpsimd_flush_cpu_state () ; 
 int /*<<< orphan*/  fpsimd_save () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  sysreg_clear_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ system_supports_sve () ; 
 int /*<<< orphan*/  update_thread_flag (int /*<<< orphan*/ ,int) ; 

void kvm_arch_vcpu_put_fp(struct kvm_vcpu *vcpu)
{
	unsigned long flags;

	local_irq_save(flags);

	if (vcpu->arch.flags & KVM_ARM64_FP_ENABLED) {
		/* Clean guest FP state to memory and invalidate cpu view */
		fpsimd_save();
		fpsimd_flush_cpu_state();
	} else if (system_supports_sve()) {
		/*
		 * The FPSIMD/SVE state in the CPU has not been touched, and we
		 * have SVE (and VHE): CPACR_EL1 (alias CPTR_EL2) has been
		 * reset to CPACR_EL1_DEFAULT by the Hyp code, disabling SVE
		 * for EL0.  To avoid spurious traps, restore the trap state
		 * seen by kvm_arch_vcpu_load_fp():
		 */
		if (vcpu->arch.flags & KVM_ARM64_HOST_SVE_ENABLED)
			sysreg_clear_set(CPACR_EL1, 0, CPACR_EL1_ZEN_EL0EN);
		else
			sysreg_clear_set(CPACR_EL1, CPACR_EL1_ZEN_EL0EN, 0);
	}

	update_thread_flag(TIF_SVE,
			   vcpu->arch.flags & KVM_ARM64_HOST_SVE_IN_USE);

	local_irq_restore(flags);
}