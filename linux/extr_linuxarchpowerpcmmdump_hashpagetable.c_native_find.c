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
typedef  void* u64 ;
struct hash_pte {int /*<<< orphan*/  r; int /*<<< orphan*/  v; } ;
struct TYPE_2__ {unsigned long shift; } ;

/* Variables and functions */
 unsigned long HPTES_PER_GROUP ; 
 scalar_t__ HPTE_V_COMPARE (unsigned long,unsigned long) ; 
 unsigned long HPTE_V_VALID ; 
 void* be64_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned long get_kernel_vsid (unsigned long,int) ; 
 unsigned long hpt_hash (unsigned long,unsigned long,int) ; 
 unsigned long hpt_vpn (unsigned long,unsigned long,int) ; 
 unsigned long hpte_encode_avpn (unsigned long,int,int) ; 
 struct hash_pte* htab_address ; 
 unsigned long htab_hash_mask ; 
 int mmu_kernel_ssize ; 
 TYPE_1__* mmu_psize_defs ; 

__attribute__((used)) static int native_find(unsigned long ea, int psize, bool primary, u64 *v, u64
		*r)
{
	struct hash_pte *hptep;
	unsigned long hash, vsid, vpn, hpte_group, want_v, hpte_v;
	int i, ssize = mmu_kernel_ssize;
	unsigned long shift = mmu_psize_defs[psize].shift;

	/* calculate hash */
	vsid = get_kernel_vsid(ea, ssize);
	vpn  = hpt_vpn(ea, vsid, ssize);
	hash = hpt_hash(vpn, shift, ssize);
	want_v = hpte_encode_avpn(vpn, psize, ssize);

	/* to check in the secondary hash table, we invert the hash */
	if (!primary)
		hash = ~hash;
	hpte_group = (hash & htab_hash_mask) * HPTES_PER_GROUP;
	for (i = 0; i < HPTES_PER_GROUP; i++) {
		hptep = htab_address + hpte_group;
		hpte_v = be64_to_cpu(hptep->v);

		if (HPTE_V_COMPARE(hpte_v, want_v) && (hpte_v & HPTE_V_VALID)) {
			/* HPTE matches */
			*v = be64_to_cpu(hptep->v);
			*r = be64_to_cpu(hptep->r);
			return 0;
		}
		++hpte_group;
	}
	return -1;
}