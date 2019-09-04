#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {TYPE_2__* apic; int /*<<< orphan*/  apic_attention; } ;
struct kvm_vcpu {TYPE_1__ arch; int /*<<< orphan*/  kvm; } ;
struct TYPE_5__ {int /*<<< orphan*/  vapic_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_APIC_CHECK_VAPIC ; 
 int /*<<< orphan*/  KVM_APIC_PV_EOI_PENDING ; 
 int /*<<< orphan*/  apic_set_tpr (TYPE_2__*,int) ; 
 int /*<<< orphan*/  apic_sync_pv_eoi_from_guest (struct kvm_vcpu*,TYPE_2__*) ; 
 scalar_t__ kvm_read_guest_cached (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void kvm_lapic_sync_from_vapic(struct kvm_vcpu *vcpu)
{
	u32 data;

	if (test_bit(KVM_APIC_PV_EOI_PENDING, &vcpu->arch.apic_attention))
		apic_sync_pv_eoi_from_guest(vcpu, vcpu->arch.apic);

	if (!test_bit(KVM_APIC_CHECK_VAPIC, &vcpu->arch.apic_attention))
		return;

	if (kvm_read_guest_cached(vcpu->kvm, &vcpu->arch.apic->vapic_cache, &data,
				  sizeof(u32)))
		return;

	apic_set_tpr(vcpu->arch.apic, data & 0xff);
}