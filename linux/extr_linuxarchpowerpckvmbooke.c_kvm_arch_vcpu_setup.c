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
struct TYPE_4__ {scalar_t__ nip; } ;
struct TYPE_6__ {int shadow_msr; int shadow_pid; int ivpr; int* ivor; TYPE_2__* shared; TYPE_1__ regs; } ;
struct kvm_vcpu {TYPE_3__ arch; int /*<<< orphan*/  vcpu_id; } ;
struct TYPE_5__ {scalar_t__ msr; int /*<<< orphan*/  pir; } ;

/* Variables and functions */
 int BOOKE_IRQPRIO_MAX ; 
 int MSR_DS ; 
 int MSR_IS ; 
 int MSR_USER ; 
 int kvmppc_core_vcpu_setup (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_init_timing_stats (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_sanity_check (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_set_gpr (struct kvm_vcpu*,int,int) ; 
 int /*<<< orphan*/  kvmppc_set_msr (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

int kvm_arch_vcpu_setup(struct kvm_vcpu *vcpu)
{
	int i;
	int r;

	vcpu->arch.regs.nip = 0;
	vcpu->arch.shared->pir = vcpu->vcpu_id;
	kvmppc_set_gpr(vcpu, 1, (16<<20) - 8); /* -8 for the callee-save LR slot */
	kvmppc_set_msr(vcpu, 0);

#ifndef CONFIG_KVM_BOOKE_HV
	vcpu->arch.shadow_msr = MSR_USER | MSR_IS | MSR_DS;
	vcpu->arch.shadow_pid = 1;
	vcpu->arch.shared->msr = 0;
#endif

	/* Eye-catching numbers so we know if the guest takes an interrupt
	 * before it's programmed its own IVPR/IVORs. */
	vcpu->arch.ivpr = 0x55550000;
	for (i = 0; i < BOOKE_IRQPRIO_MAX; i++)
		vcpu->arch.ivor[i] = 0x7700 | i * 4;

	kvmppc_init_timing_stats(vcpu);

	r = kvmppc_core_vcpu_setup(vcpu);
	kvmppc_sanity_check(vcpu);
	return r;
}