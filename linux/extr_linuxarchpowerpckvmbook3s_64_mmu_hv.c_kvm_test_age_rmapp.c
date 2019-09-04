#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct revmap_entry {unsigned long forw; } ;
struct TYPE_4__ {unsigned long* rmap; } ;
struct kvm_memory_slot {unsigned long base_gfn; TYPE_1__ arch; } ;
struct TYPE_5__ {scalar_t__ virt; struct revmap_entry* rev; } ;
struct TYPE_6__ {TYPE_2__ hpt; } ;
struct kvm {TYPE_3__ arch; } ;

/* Variables and functions */
 int HPTE_R_R ; 
 unsigned long KVMPPC_RMAP_INDEX ; 
 unsigned long KVMPPC_RMAP_PRESENT ; 
 unsigned long KVMPPC_RMAP_REFERENCED ; 
 int be64_to_cpu (unsigned long) ; 
 int /*<<< orphan*/  lock_rmap (unsigned long*) ; 
 int /*<<< orphan*/  unlock_rmap (unsigned long*) ; 

__attribute__((used)) static int kvm_test_age_rmapp(struct kvm *kvm, struct kvm_memory_slot *memslot,
			      unsigned long gfn)
{
	struct revmap_entry *rev = kvm->arch.hpt.rev;
	unsigned long head, i, j;
	unsigned long *hp;
	int ret = 1;
	unsigned long *rmapp;

	rmapp = &memslot->arch.rmap[gfn - memslot->base_gfn];
	if (*rmapp & KVMPPC_RMAP_REFERENCED)
		return 1;

	lock_rmap(rmapp);
	if (*rmapp & KVMPPC_RMAP_REFERENCED)
		goto out;

	if (*rmapp & KVMPPC_RMAP_PRESENT) {
		i = head = *rmapp & KVMPPC_RMAP_INDEX;
		do {
			hp = (unsigned long *)(kvm->arch.hpt.virt + (i << 4));
			j = rev[i].forw;
			if (be64_to_cpu(hp[1]) & HPTE_R_R)
				goto out;
		} while ((i = j) != head);
	}
	ret = 0;

 out:
	unlock_rmap(rmapp);
	return ret;
}