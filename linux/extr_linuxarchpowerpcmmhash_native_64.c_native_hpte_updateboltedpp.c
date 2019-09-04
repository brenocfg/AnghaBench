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
struct hash_pte {int /*<<< orphan*/  r; } ;

/* Variables and functions */
 unsigned long HPTE_R_N ; 
 unsigned long HPTE_R_PPP ; 
 unsigned long be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be64 (unsigned long) ; 
 unsigned long get_kernel_vsid (unsigned long,int) ; 
 unsigned long hpt_vpn (unsigned long,unsigned long,int) ; 
 struct hash_pte* htab_address ; 
 long native_hpte_find (unsigned long,int,int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  tlbie (unsigned long,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void native_hpte_updateboltedpp(unsigned long newpp, unsigned long ea,
				       int psize, int ssize)
{
	unsigned long vpn;
	unsigned long vsid;
	long slot;
	struct hash_pte *hptep;

	vsid = get_kernel_vsid(ea, ssize);
	vpn = hpt_vpn(ea, vsid, ssize);

	slot = native_hpte_find(vpn, psize, ssize);
	if (slot == -1)
		panic("could not find page to bolt\n");
	hptep = htab_address + slot;

	/* Update the HPTE */
	hptep->r = cpu_to_be64((be64_to_cpu(hptep->r) &
				~(HPTE_R_PPP | HPTE_R_N)) |
			       (newpp & (HPTE_R_PPP | HPTE_R_N)));
	/*
	 * Ensure it is out of the tlb too. Bolted entries base and
	 * actual page size will be same.
	 */
	tlbie(vpn, psize, psize, ssize, 0);
}