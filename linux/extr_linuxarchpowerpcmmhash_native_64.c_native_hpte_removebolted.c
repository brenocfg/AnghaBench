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
 int ENOENT ; 
 int HPTE_V_BOLTED ; 
 int /*<<< orphan*/  VM_WARN_ON (int) ; 
 int be64_to_cpu (scalar_t__) ; 
 unsigned long get_kernel_vsid (unsigned long,int) ; 
 unsigned long hpt_vpn (unsigned long,unsigned long,int) ; 
 struct hash_pte* htab_address ; 
 long native_hpte_find (unsigned long,int,int) ; 
 int /*<<< orphan*/  tlbie (unsigned long,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int native_hpte_removebolted(unsigned long ea, int psize, int ssize)
{
	unsigned long vpn;
	unsigned long vsid;
	long slot;
	struct hash_pte *hptep;

	vsid = get_kernel_vsid(ea, ssize);
	vpn = hpt_vpn(ea, vsid, ssize);

	slot = native_hpte_find(vpn, psize, ssize);
	if (slot == -1)
		return -ENOENT;

	hptep = htab_address + slot;

	VM_WARN_ON(!(be64_to_cpu(hptep->v) & HPTE_V_BOLTED));

	/* Invalidate the hpte */
	hptep->v = 0;

	/* Invalidate the TLB */
	tlbie(vpn, psize, psize, ssize, 0);
	return 0;
}