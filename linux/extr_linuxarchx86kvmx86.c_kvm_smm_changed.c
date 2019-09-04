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
struct TYPE_2__ {int hflags; int /*<<< orphan*/  smbase; } ;
struct kvm_vcpu {TYPE_1__ arch; int /*<<< orphan*/  vcpu_id; } ;

/* Variables and functions */
 int HF_SMM_MASK ; 
 int /*<<< orphan*/  KVM_REQ_EVENT ; 
 int /*<<< orphan*/  kvm_make_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_mmu_reset_context (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  trace_kvm_enter_smm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void kvm_smm_changed(struct kvm_vcpu *vcpu)
{
	if (!(vcpu->arch.hflags & HF_SMM_MASK)) {
		/* This is a good place to trace that we are exiting SMM.  */
		trace_kvm_enter_smm(vcpu->vcpu_id, vcpu->arch.smbase, false);

		/* Process a latched INIT or SMI, if any.  */
		kvm_make_request(KVM_REQ_EVENT, vcpu);
	}

	kvm_mmu_reset_context(vcpu);
}