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
struct TYPE_3__ {struct kvm_lapic* apic; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct TYPE_4__ {int /*<<< orphan*/  pending; scalar_t__ target_expiration; scalar_t__ tscdeadline; } ;
struct kvm_lapic {TYPE_2__ lapic_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  APIC_LVTT ; 
 scalar_t__ apic_lvtt_oneshot (struct kvm_lapic*) ; 
 scalar_t__ apic_lvtt_tscdeadline (struct kvm_lapic*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_apic_local_deliver (struct kvm_lapic*,int /*<<< orphan*/ ) ; 

void kvm_inject_apic_timer_irqs(struct kvm_vcpu *vcpu)
{
	struct kvm_lapic *apic = vcpu->arch.apic;

	if (atomic_read(&apic->lapic_timer.pending) > 0) {
		kvm_apic_local_deliver(apic, APIC_LVTT);
		if (apic_lvtt_tscdeadline(apic))
			apic->lapic_timer.tscdeadline = 0;
		if (apic_lvtt_oneshot(apic)) {
			apic->lapic_timer.tscdeadline = 0;
			apic->lapic_timer.target_expiration = 0;
		}
		atomic_set(&apic->lapic_timer.pending, 0);
	}
}