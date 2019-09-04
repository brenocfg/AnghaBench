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
struct vcpu_svm {int nrips_enabled; int /*<<< orphan*/  vcpu; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  X86_FEATURE_NRIPS ; 
 int /*<<< orphan*/  X86_FEATURE_X2APIC ; 
 int /*<<< orphan*/  guest_cpuid_clear (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  guest_cpuid_has (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_vcpu_apicv_active (struct kvm_vcpu*) ; 
 struct vcpu_svm* to_svm (struct kvm_vcpu*) ; 

__attribute__((used)) static void svm_cpuid_update(struct kvm_vcpu *vcpu)
{
	struct vcpu_svm *svm = to_svm(vcpu);

	/* Update nrips enabled cache */
	svm->nrips_enabled = !!guest_cpuid_has(&svm->vcpu, X86_FEATURE_NRIPS);

	if (!kvm_vcpu_apicv_active(vcpu))
		return;

	guest_cpuid_clear(vcpu, X86_FEATURE_X2APIC);
}