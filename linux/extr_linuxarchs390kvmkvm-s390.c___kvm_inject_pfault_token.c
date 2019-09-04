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
struct kvm_vcpu {int /*<<< orphan*/  kvm; } ;
struct TYPE_3__ {unsigned long ext_params2; } ;
struct TYPE_4__ {TYPE_1__ ext; } ;
struct kvm_s390_irq {int /*<<< orphan*/  type; TYPE_2__ u; } ;
struct kvm_s390_interrupt {unsigned long parm64; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_S390_INT_PFAULT_DONE ; 
 int /*<<< orphan*/  KVM_S390_INT_PFAULT_INIT ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_s390_inject_vcpu (struct kvm_vcpu*,struct kvm_s390_irq*) ; 
 int /*<<< orphan*/  kvm_s390_inject_vm (int /*<<< orphan*/ ,struct kvm_s390_interrupt*) ; 

__attribute__((used)) static void __kvm_inject_pfault_token(struct kvm_vcpu *vcpu, bool start_token,
				      unsigned long token)
{
	struct kvm_s390_interrupt inti;
	struct kvm_s390_irq irq;

	if (start_token) {
		irq.u.ext.ext_params2 = token;
		irq.type = KVM_S390_INT_PFAULT_INIT;
		WARN_ON_ONCE(kvm_s390_inject_vcpu(vcpu, &irq));
	} else {
		inti.type = KVM_S390_INT_PFAULT_DONE;
		inti.parm64 = token;
		WARN_ON_ONCE(kvm_s390_inject_vm(vcpu->kvm, &inti));
	}
}