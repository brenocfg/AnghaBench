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
struct TYPE_2__ {int /*<<< orphan*/  apic; } ;
struct kvm_vcpu {int /*<<< orphan*/  cpu; TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVM_AVIC_DOORBELL ; 
 scalar_t__ avic_vcpu_is_running (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_cpu_get_apicid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_lapic_set_irr (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_vcpu_wake_up (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void svm_deliver_avic_intr(struct kvm_vcpu *vcpu, int vec)
{
	kvm_lapic_set_irr(vec, vcpu->arch.apic);
	smp_mb__after_atomic();

	if (avic_vcpu_is_running(vcpu))
		wrmsrl(SVM_AVIC_DOORBELL,
		       kvm_cpu_get_apicid(vcpu->cpu));
	else
		kvm_vcpu_wake_up(vcpu);
}