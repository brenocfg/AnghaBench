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
struct TYPE_4__ {int apic_base; struct kvm_lapic* apic; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct TYPE_3__ {int /*<<< orphan*/  timer; } ;
struct kvm_lapic {scalar_t__ regs; int /*<<< orphan*/  sw_enabled; TYPE_1__ lapic_timer; } ;

/* Variables and functions */
 int MSR_IA32_APICBASE_ENABLE ; 
 int /*<<< orphan*/  apic_hw_disabled ; 
 int /*<<< orphan*/  apic_sw_disabled ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct kvm_lapic*) ; 
 int /*<<< orphan*/  static_key_slow_dec_deferred (int /*<<< orphan*/ *) ; 

void kvm_free_lapic(struct kvm_vcpu *vcpu)
{
	struct kvm_lapic *apic = vcpu->arch.apic;

	if (!vcpu->arch.apic)
		return;

	hrtimer_cancel(&apic->lapic_timer.timer);

	if (!(vcpu->arch.apic_base & MSR_IA32_APICBASE_ENABLE))
		static_key_slow_dec_deferred(&apic_hw_disabled);

	if (!apic->sw_enabled)
		static_key_slow_dec_deferred(&apic_sw_disabled);

	if (apic->regs)
		free_page((unsigned long)apic->regs);

	kfree(apic);
}