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
 int /*<<< orphan*/  DBG_LOW (char*,unsigned long) ; 
 int HPTES_PER_GROUP ; 
 unsigned long HPTE_V_BOLTED ; 
 unsigned long HPTE_V_VALID ; 
 unsigned long be64_to_cpu (scalar_t__) ; 
 struct hash_pte* htab_address ; 
 int mftb () ; 
 int /*<<< orphan*/  native_lock_hpte (struct hash_pte*) ; 
 int /*<<< orphan*/  native_unlock_hpte (struct hash_pte*) ; 

__attribute__((used)) static long native_hpte_remove(unsigned long hpte_group)
{
	struct hash_pte *hptep;
	int i;
	int slot_offset;
	unsigned long hpte_v;

	DBG_LOW("    remove(group=%lx)\n", hpte_group);

	/* pick a random entry to start at */
	slot_offset = mftb() & 0x7;

	for (i = 0; i < HPTES_PER_GROUP; i++) {
		hptep = htab_address + hpte_group + slot_offset;
		hpte_v = be64_to_cpu(hptep->v);

		if ((hpte_v & HPTE_V_VALID) && !(hpte_v & HPTE_V_BOLTED)) {
			/* retry with lock held */
			native_lock_hpte(hptep);
			hpte_v = be64_to_cpu(hptep->v);
			if ((hpte_v & HPTE_V_VALID)
			    && !(hpte_v & HPTE_V_BOLTED))
				break;
			native_unlock_hpte(hptep);
		}

		slot_offset++;
		slot_offset &= 0x7;
	}

	if (i == HPTES_PER_GROUP)
		return -1;

	/* Invalidate the hpte. NOTE: this also unlocks it */
	hptep->v = 0;

	return i;
}