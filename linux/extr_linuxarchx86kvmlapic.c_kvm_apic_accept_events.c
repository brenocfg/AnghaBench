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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {scalar_t__ mp_state; struct kvm_lapic* apic; } ;
struct kvm_vcpu {TYPE_1__ arch; int /*<<< orphan*/  vcpu_id; } ;
struct kvm_lapic {unsigned long pending_events; int /*<<< orphan*/  sipi_vector; int /*<<< orphan*/  vcpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_APIC_INIT ; 
 int /*<<< orphan*/  KVM_APIC_SIPI ; 
 scalar_t__ KVM_MP_STATE_INIT_RECEIVED ; 
 void* KVM_MP_STATE_RUNNABLE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  apic_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 scalar_t__ is_smm (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_vcpu_deliver_sipi_vector (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 scalar_t__ kvm_vcpu_is_bsp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_vcpu_reset (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  lapic_in_kernel (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 unsigned long xchg (unsigned long*,int /*<<< orphan*/ ) ; 

void kvm_apic_accept_events(struct kvm_vcpu *vcpu)
{
	struct kvm_lapic *apic = vcpu->arch.apic;
	u8 sipi_vector;
	unsigned long pe;

	if (!lapic_in_kernel(vcpu) || !apic->pending_events)
		return;

	/*
	 * INITs are latched while in SMM.  Because an SMM CPU cannot
	 * be in KVM_MP_STATE_INIT_RECEIVED state, just eat SIPIs
	 * and delay processing of INIT until the next RSM.
	 */
	if (is_smm(vcpu)) {
		WARN_ON_ONCE(vcpu->arch.mp_state == KVM_MP_STATE_INIT_RECEIVED);
		if (test_bit(KVM_APIC_SIPI, &apic->pending_events))
			clear_bit(KVM_APIC_SIPI, &apic->pending_events);
		return;
	}

	pe = xchg(&apic->pending_events, 0);
	if (test_bit(KVM_APIC_INIT, &pe)) {
		kvm_vcpu_reset(vcpu, true);
		if (kvm_vcpu_is_bsp(apic->vcpu))
			vcpu->arch.mp_state = KVM_MP_STATE_RUNNABLE;
		else
			vcpu->arch.mp_state = KVM_MP_STATE_INIT_RECEIVED;
	}
	if (test_bit(KVM_APIC_SIPI, &pe) &&
	    vcpu->arch.mp_state == KVM_MP_STATE_INIT_RECEIVED) {
		/* evaluate pending_events before reading the vector */
		smp_rmb();
		sipi_vector = apic->sipi_vector;
		apic_debug("vcpu %d received sipi with vector # %x\n",
			 vcpu->vcpu_id, sipi_vector);
		kvm_vcpu_deliver_sipi_vector(vcpu, sipi_vector);
		vcpu->arch.mp_state = KVM_MP_STATE_RUNNABLE;
	}
}