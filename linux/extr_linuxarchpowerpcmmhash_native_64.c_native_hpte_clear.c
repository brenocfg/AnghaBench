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
 unsigned long HPTES_PER_GROUP ; 
 unsigned long HPTE_V_VALID ; 
 int /*<<< orphan*/  ___tlbie (unsigned long,int,int,int) ; 
 unsigned long be64_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  hpte_decode (struct hash_pte*,unsigned long,int*,int*,int*,unsigned long*) ; 
 struct hash_pte* htab_address ; 
 int htab_hash_mask ; 

__attribute__((used)) static void native_hpte_clear(void)
{
	unsigned long vpn = 0;
	unsigned long slot, slots;
	struct hash_pte *hptep = htab_address;
	unsigned long hpte_v;
	unsigned long pteg_count;
	int psize, apsize, ssize;

	pteg_count = htab_hash_mask + 1;

	slots = pteg_count * HPTES_PER_GROUP;

	for (slot = 0; slot < slots; slot++, hptep++) {
		/*
		 * we could lock the pte here, but we are the only cpu
		 * running,  right?  and for crash dump, we probably
		 * don't want to wait for a maybe bad cpu.
		 */
		hpte_v = be64_to_cpu(hptep->v);

		/*
		 * Call __tlbie() here rather than tlbie() since we can't take the
		 * native_tlbie_lock.
		 */
		if (hpte_v & HPTE_V_VALID) {
			hpte_decode(hptep, slot, &psize, &apsize, &ssize, &vpn);
			hptep->v = 0;
			___tlbie(vpn, psize, apsize, ssize);
		}
	}

	asm volatile("eieio; tlbsync; ptesync":::"memory");
}