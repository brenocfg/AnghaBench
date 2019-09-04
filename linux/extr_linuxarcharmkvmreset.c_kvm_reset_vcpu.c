#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int reset; unsigned long pc; int /*<<< orphan*/  r0; scalar_t__ be; } ;
struct TYPE_4__ {int /*<<< orphan*/  gp_regs; } ;
struct TYPE_6__ {int target; TYPE_2__ reset_state; TYPE_1__ ctxt; int /*<<< orphan*/  midr; } ;
struct kvm_vcpu {TYPE_3__ arch; } ;
struct kvm_regs {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
#define  KVM_ARM_TARGET_CORTEX_A15 129 
#define  KVM_ARM_TARGET_CORTEX_A7 128 
 scalar_t__ READ_ONCE (int) ; 
 struct kvm_regs cortexa_regs_reset ; 
 int /*<<< orphan*/  kvm_reset_coprocs (struct kvm_vcpu*) ; 
 int kvm_timer_vcpu_reset (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_vcpu_set_be (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct kvm_regs*,int) ; 
 int /*<<< orphan*/  read_cpuid_id () ; 
 unsigned long* vcpu_pc (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_set_reg (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcpu_set_thumb (struct kvm_vcpu*) ; 

int kvm_reset_vcpu(struct kvm_vcpu *vcpu)
{
	struct kvm_regs *reset_regs;

	switch (vcpu->arch.target) {
	case KVM_ARM_TARGET_CORTEX_A7:
	case KVM_ARM_TARGET_CORTEX_A15:
		reset_regs = &cortexa_regs_reset;
		vcpu->arch.midr = read_cpuid_id();
		break;
	default:
		return -ENODEV;
	}

	/* Reset core registers */
	memcpy(&vcpu->arch.ctxt.gp_regs, reset_regs, sizeof(vcpu->arch.ctxt.gp_regs));

	/* Reset CP15 registers */
	kvm_reset_coprocs(vcpu);

	/*
	 * Additional reset state handling that PSCI may have imposed on us.
	 * Must be done after all the sys_reg reset.
	 */
	if (READ_ONCE(vcpu->arch.reset_state.reset)) {
		unsigned long target_pc = vcpu->arch.reset_state.pc;

		/* Gracefully handle Thumb2 entry point */
		if (target_pc & 1) {
			target_pc &= ~1UL;
			vcpu_set_thumb(vcpu);
		}

		/* Propagate caller endianness */
		if (vcpu->arch.reset_state.be)
			kvm_vcpu_set_be(vcpu);

		*vcpu_pc(vcpu) = target_pc;
		vcpu_set_reg(vcpu, 0, vcpu->arch.reset_state.r0);

		vcpu->arch.reset_state.reset = false;
	}

	/* Reset arch_timer context */
	return kvm_timer_vcpu_reset(vcpu);
}