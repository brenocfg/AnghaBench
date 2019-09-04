#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* shared; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct TYPE_3__ {int msr; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMULATED_MTMSRWE_EXITS ; 
 int /*<<< orphan*/  KVM_REQ_UNHALT ; 
 int MSR_WE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  hard_irq_disable () ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 int /*<<< orphan*/  kvm_clear_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 scalar_t__ kvm_request_pending (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_vcpu_block (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_core_check_exceptions (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_set_exit_type (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_enable () ; 

int kvmppc_core_prepare_to_enter(struct kvm_vcpu *vcpu)
{
	int r = 0;
	WARN_ON_ONCE(!irqs_disabled());

	kvmppc_core_check_exceptions(vcpu);

	if (kvm_request_pending(vcpu)) {
		/* Exception delivery raised request; start over */
		return 1;
	}

	if (vcpu->arch.shared->msr & MSR_WE) {
		local_irq_enable();
		kvm_vcpu_block(vcpu);
		kvm_clear_request(KVM_REQ_UNHALT, vcpu);
		hard_irq_disable();

		kvmppc_set_exit_type(vcpu, EMULATED_MTMSRWE_EXITS);
		r = 1;
	};

	return r;
}