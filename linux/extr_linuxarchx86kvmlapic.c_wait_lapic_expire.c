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
typedef  scalar_t__ u64 ;
struct TYPE_3__ {struct kvm_lapic* apic; } ;
struct kvm_vcpu {int /*<<< orphan*/  vcpu_id; TYPE_1__ arch; } ;
struct TYPE_4__ {scalar_t__ expired_tscdeadline; } ;
struct kvm_lapic {TYPE_2__ lapic_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  __delay (int /*<<< orphan*/ ) ; 
 scalar_t__ kvm_read_l1_tsc (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lapic_in_kernel (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  lapic_timer_advance_ns ; 
 int /*<<< orphan*/  lapic_timer_int_injected (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  min (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsec_to_cycles (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdtsc () ; 
 int /*<<< orphan*/  trace_kvm_wait_lapic_expire (int /*<<< orphan*/ ,scalar_t__) ; 

void wait_lapic_expire(struct kvm_vcpu *vcpu)
{
	struct kvm_lapic *apic = vcpu->arch.apic;
	u64 guest_tsc, tsc_deadline;

	if (!lapic_in_kernel(vcpu))
		return;

	if (apic->lapic_timer.expired_tscdeadline == 0)
		return;

	if (!lapic_timer_int_injected(vcpu))
		return;

	tsc_deadline = apic->lapic_timer.expired_tscdeadline;
	apic->lapic_timer.expired_tscdeadline = 0;
	guest_tsc = kvm_read_l1_tsc(vcpu, rdtsc());
	trace_kvm_wait_lapic_expire(vcpu->vcpu_id, guest_tsc - tsc_deadline);

	/* __delay is delay_tsc whenever the hardware has TSC, thus always.  */
	if (guest_tsc < tsc_deadline)
		__delay(min(tsc_deadline - guest_tsc,
			nsec_to_cycles(vcpu, lapic_timer_advance_ns)));
}