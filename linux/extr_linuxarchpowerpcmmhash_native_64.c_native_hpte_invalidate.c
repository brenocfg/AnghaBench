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
struct hash_pte {scalar_t__ v; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_LOW (char*,unsigned long,unsigned long) ; 
 scalar_t__ HPTE_V_COMPARE (unsigned long,unsigned long) ; 
 unsigned long HPTE_V_VALID ; 
 unsigned long hpte_encode_avpn (unsigned long,int,int) ; 
 unsigned long hpte_get_old_v (struct hash_pte*) ; 
 struct hash_pte* htab_address ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  native_lock_hpte (struct hash_pte*) ; 
 int /*<<< orphan*/  native_unlock_hpte (struct hash_pte*) ; 
 int /*<<< orphan*/  tlbie (unsigned long,int,int,int,int) ; 

__attribute__((used)) static void native_hpte_invalidate(unsigned long slot, unsigned long vpn,
				   int bpsize, int apsize, int ssize, int local)
{
	struct hash_pte *hptep = htab_address + slot;
	unsigned long hpte_v;
	unsigned long want_v;
	unsigned long flags;

	local_irq_save(flags);

	DBG_LOW("    invalidate(vpn=%016lx, hash: %lx)\n", vpn, slot);

	want_v = hpte_encode_avpn(vpn, bpsize, ssize);
	hpte_v = hpte_get_old_v(hptep);

	if (HPTE_V_COMPARE(hpte_v, want_v) && (hpte_v & HPTE_V_VALID)) {
		native_lock_hpte(hptep);
		/* recheck with locks held */
		hpte_v = hpte_get_old_v(hptep);

		if (HPTE_V_COMPARE(hpte_v, want_v) && (hpte_v & HPTE_V_VALID))
			/* Invalidate the hpte. NOTE: this also unlocks it */
			hptep->v = 0;
		else
			native_unlock_hpte(hptep);
	}
	/*
	 * We need to invalidate the TLB always because hpte_remove doesn't do
	 * a tlb invalidate. If a hash bucket gets full, we "evict" a more/less
	 * random entry from it. When we do that we don't invalidate the TLB
	 * (hpte_remove) because we assume the old translation is still
	 * technically "valid".
	 */
	tlbie(vpn, bpsize, apsize, ssize, local);

	local_irq_restore(flags);
}