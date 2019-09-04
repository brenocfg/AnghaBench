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
typedef  int /*<<< orphan*/  u64 ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; } ;
struct kvm_memory_slot {int dummy; } ;

/* Variables and functions */
 int kvm_mmu_slot_gfn_write_protect (int /*<<< orphan*/ ,struct kvm_memory_slot*,int /*<<< orphan*/ ) ; 
 struct kvm_memory_slot* kvm_vcpu_gfn_to_memslot (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool rmap_write_protect(struct kvm_vcpu *vcpu, u64 gfn)
{
	struct kvm_memory_slot *slot;

	slot = kvm_vcpu_gfn_to_memslot(vcpu, gfn);
	return kvm_mmu_slot_gfn_write_protect(vcpu->kvm, slot, gfn);
}