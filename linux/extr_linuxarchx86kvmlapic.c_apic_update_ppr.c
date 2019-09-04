#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct kvm_lapic {int /*<<< orphan*/  vcpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_REQ_EVENT ; 
 scalar_t__ __apic_update_ppr (struct kvm_lapic*,int /*<<< orphan*/ *) ; 
 int apic_has_interrupt_for_ppr (struct kvm_lapic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_make_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void apic_update_ppr(struct kvm_lapic *apic)
{
	u32 ppr;

	if (__apic_update_ppr(apic, &ppr) &&
	    apic_has_interrupt_for_ppr(apic, ppr) != -1)
		kvm_make_request(KVM_REQ_EVENT, apic->vcpu);
}