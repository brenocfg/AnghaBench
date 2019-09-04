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
struct kvm {int dummy; } ;

/* Variables and functions */
 int APIC_DEFAULT_PHYS_BASE ; 
 int /*<<< orphan*/  KVM_REQ_APIC_PAGE_RELOAD ; 
 int PAGE_SHIFT ; 
 unsigned long gfn_to_hva (struct kvm*,int) ; 
 int /*<<< orphan*/  kvm_make_all_cpus_request (struct kvm*,int /*<<< orphan*/ ) ; 

int kvm_arch_mmu_notifier_invalidate_range(struct kvm *kvm,
		unsigned long start, unsigned long end,
		bool blockable)
{
	unsigned long apic_address;

	/*
	 * The physical address of apic access page is stored in the VMCS.
	 * Update it when it becomes invalid.
	 */
	apic_address = gfn_to_hva(kvm, APIC_DEFAULT_PHYS_BASE >> PAGE_SHIFT);
	if (start <= apic_address && apic_address < end)
		kvm_make_all_cpus_request(kvm, KVM_REQ_APIC_PAGE_RELOAD);

	return 0;
}