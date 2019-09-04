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
typedef  int u32 ;
struct TYPE_2__ {struct kvm_lapic* apic; int /*<<< orphan*/  apic_attention; } ;
struct kvm_vcpu {TYPE_1__ arch; int /*<<< orphan*/  kvm; } ;
struct kvm_lapic {int /*<<< orphan*/  vapic_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  APIC_TASKPRI ; 
 int /*<<< orphan*/  KVM_APIC_CHECK_VAPIC ; 
 int apic_find_highest_irr (struct kvm_lapic*) ; 
 int apic_find_highest_isr (struct kvm_lapic*) ; 
 int /*<<< orphan*/  apic_sync_pv_eoi_to_guest (struct kvm_vcpu*,struct kvm_lapic*) ; 
 int kvm_lapic_get_reg (struct kvm_lapic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_write_guest_cached (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void kvm_lapic_sync_to_vapic(struct kvm_vcpu *vcpu)
{
	u32 data, tpr;
	int max_irr, max_isr;
	struct kvm_lapic *apic = vcpu->arch.apic;

	apic_sync_pv_eoi_to_guest(vcpu, apic);

	if (!test_bit(KVM_APIC_CHECK_VAPIC, &vcpu->arch.apic_attention))
		return;

	tpr = kvm_lapic_get_reg(apic, APIC_TASKPRI) & 0xff;
	max_irr = apic_find_highest_irr(apic);
	if (max_irr < 0)
		max_irr = 0;
	max_isr = apic_find_highest_isr(apic);
	if (max_isr < 0)
		max_isr = 0;
	data = (tpr & 0xff) | ((max_isr & 0xf0) << 8) | (max_irr << 24);

	kvm_write_guest_cached(vcpu->kvm, &vcpu->arch.apic->vapic_cache, &data,
				sizeof(u32));
}