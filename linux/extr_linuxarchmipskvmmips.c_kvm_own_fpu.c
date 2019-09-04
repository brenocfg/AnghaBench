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
struct mips_coproc {int dummy; } ;
struct TYPE_2__ {int aux_inuse; struct mips_coproc* cop0; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int KVM_MIPS_AUX_FPU ; 
 int KVM_MIPS_AUX_MSA ; 
 int /*<<< orphan*/  KVM_TRACE_AUX_ENABLE ; 
 int /*<<< orphan*/  KVM_TRACE_AUX_FPU ; 
 int /*<<< orphan*/  KVM_TRACE_AUX_RESTORE ; 
 int /*<<< orphan*/  MIPS_CONF5_FRE ; 
 unsigned int ST0_CU1 ; 
 unsigned int ST0_FR ; 
 int /*<<< orphan*/  __kvm_restore_fpu (TYPE_1__*) ; 
 int /*<<< orphan*/  change_c0_config5 (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  change_c0_status (unsigned int,unsigned int) ; 
 scalar_t__ cpu_has_fre ; 
 scalar_t__ cpu_has_msa ; 
 int /*<<< orphan*/  enable_fpu_hazard () ; 
 int /*<<< orphan*/  kvm_lose_fpu (struct kvm_vcpu*) ; 
 unsigned int kvm_read_c0_guest_config5 (struct mips_coproc*) ; 
 unsigned int kvm_read_c0_guest_status (struct mips_coproc*) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  trace_kvm_aux (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void kvm_own_fpu(struct kvm_vcpu *vcpu)
{
	struct mips_coproc *cop0 = vcpu->arch.cop0;
	unsigned int sr, cfg5;

	preempt_disable();

	sr = kvm_read_c0_guest_status(cop0);

	/*
	 * If MSA state is already live, it is undefined how it interacts with
	 * FR=0 FPU state, and we don't want to hit reserved instruction
	 * exceptions trying to save the MSA state later when CU=1 && FR=1, so
	 * play it safe and save it first.
	 *
	 * In theory we shouldn't ever hit this case since kvm_lose_fpu() should
	 * get called when guest CU1 is set, however we can't trust the guest
	 * not to clobber the status register directly via the commpage.
	 */
	if (cpu_has_msa && sr & ST0_CU1 && !(sr & ST0_FR) &&
	    vcpu->arch.aux_inuse & KVM_MIPS_AUX_MSA)
		kvm_lose_fpu(vcpu);

	/*
	 * Enable FPU for guest
	 * We set FR and FRE according to guest context
	 */
	change_c0_status(ST0_CU1 | ST0_FR, sr);
	if (cpu_has_fre) {
		cfg5 = kvm_read_c0_guest_config5(cop0);
		change_c0_config5(MIPS_CONF5_FRE, cfg5);
	}
	enable_fpu_hazard();

	/* If guest FPU state not active, restore it now */
	if (!(vcpu->arch.aux_inuse & KVM_MIPS_AUX_FPU)) {
		__kvm_restore_fpu(&vcpu->arch);
		vcpu->arch.aux_inuse |= KVM_MIPS_AUX_FPU;
		trace_kvm_aux(vcpu, KVM_TRACE_AUX_RESTORE, KVM_TRACE_AUX_FPU);
	} else {
		trace_kvm_aux(vcpu, KVM_TRACE_AUX_ENABLE, KVM_TRACE_AUX_FPU);
	}

	preempt_enable();
}