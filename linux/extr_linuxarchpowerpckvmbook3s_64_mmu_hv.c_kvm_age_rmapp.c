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
struct revmap_entry {unsigned long forw; int guest_rpte; } ;
struct TYPE_4__ {unsigned long* rmap; } ;
struct kvm_memory_slot {unsigned long base_gfn; TYPE_1__ arch; } ;
struct TYPE_5__ {scalar_t__ virt; struct revmap_entry* rev; } ;
struct TYPE_6__ {TYPE_2__ hpt; } ;
struct kvm {TYPE_3__ arch; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int HPTE_R_R ; 
 int HPTE_V_HVLOCK ; 
 int HPTE_V_VALID ; 
 unsigned long KVMPPC_RMAP_INDEX ; 
 unsigned long KVMPPC_RMAP_PRESENT ; 
 unsigned long KVMPPC_RMAP_REFERENCED ; 
 int /*<<< orphan*/  __unlock_hpte (int /*<<< orphan*/ *,int) ; 
 int be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  kvmppc_clear_ref_hpte (struct kvm*,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  lock_rmap (unsigned long*) ; 
 int /*<<< orphan*/  note_hpte_modification (struct kvm*,struct revmap_entry*) ; 
 int /*<<< orphan*/  try_lock_hpte (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  unlock_rmap (unsigned long*) ; 

__attribute__((used)) static int kvm_age_rmapp(struct kvm *kvm, struct kvm_memory_slot *memslot,
			 unsigned long gfn)
{
	struct revmap_entry *rev = kvm->arch.hpt.rev;
	unsigned long head, i, j;
	__be64 *hptep;
	int ret = 0;
	unsigned long *rmapp;

	rmapp = &memslot->arch.rmap[gfn - memslot->base_gfn];
 retry:
	lock_rmap(rmapp);
	if (*rmapp & KVMPPC_RMAP_REFERENCED) {
		*rmapp &= ~KVMPPC_RMAP_REFERENCED;
		ret = 1;
	}
	if (!(*rmapp & KVMPPC_RMAP_PRESENT)) {
		unlock_rmap(rmapp);
		return ret;
	}

	i = head = *rmapp & KVMPPC_RMAP_INDEX;
	do {
		hptep = (__be64 *) (kvm->arch.hpt.virt + (i << 4));
		j = rev[i].forw;

		/* If this HPTE isn't referenced, ignore it */
		if (!(be64_to_cpu(hptep[1]) & HPTE_R_R))
			continue;

		if (!try_lock_hpte(hptep, HPTE_V_HVLOCK)) {
			/* unlock rmap before spinning on the HPTE lock */
			unlock_rmap(rmapp);
			while (be64_to_cpu(hptep[0]) & HPTE_V_HVLOCK)
				cpu_relax();
			goto retry;
		}

		/* Now check and modify the HPTE */
		if ((be64_to_cpu(hptep[0]) & HPTE_V_VALID) &&
		    (be64_to_cpu(hptep[1]) & HPTE_R_R)) {
			kvmppc_clear_ref_hpte(kvm, hptep, i);
			if (!(rev[i].guest_rpte & HPTE_R_R)) {
				rev[i].guest_rpte |= HPTE_R_R;
				note_hpte_modification(kvm, &rev[i]);
			}
			ret = 1;
		}
		__unlock_hpte(hptep, be64_to_cpu(hptep[0]));
	} while ((i = j) != head);

	unlock_rmap(rmapp);
	return ret;
}