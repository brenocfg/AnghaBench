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
struct kvm_vcpu {int /*<<< orphan*/  cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_FTR_ARCH_207S ; 
 int /*<<< orphan*/  CPU_FTR_HVMODE ; 
 int LPCR_AIL ; 
 int /*<<< orphan*/  SPRN_LPCR ; 
 scalar_t__ cpu_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmppc_fixup_split_real (struct kvm_vcpu*) ; 
 scalar_t__ kvmppc_is_split_real (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_restore_tm_pr (struct kvm_vcpu*) ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static void kvmppc_core_vcpu_load_pr(struct kvm_vcpu *vcpu, int cpu)
{
#ifdef CONFIG_PPC_BOOK3S_64
	struct kvmppc_book3s_shadow_vcpu *svcpu = svcpu_get(vcpu);
	memcpy(svcpu->slb, to_book3s(vcpu)->slb_shadow, sizeof(svcpu->slb));
	svcpu->slb_max = to_book3s(vcpu)->slb_shadow_max;
	svcpu->in_use = 0;
	svcpu_put(svcpu);
#endif

	/* Disable AIL if supported */
	if (cpu_has_feature(CPU_FTR_HVMODE) &&
	    cpu_has_feature(CPU_FTR_ARCH_207S))
		mtspr(SPRN_LPCR, mfspr(SPRN_LPCR) & ~LPCR_AIL);

	vcpu->cpu = smp_processor_id();
#ifdef CONFIG_PPC_BOOK3S_32
	current->thread.kvm_shadow_vcpu = vcpu->arch.shadow_vcpu;
#endif

	if (kvmppc_is_split_real(vcpu))
		kvmppc_fixup_split_real(vcpu);

	kvmppc_restore_tm_pr(vcpu);
}