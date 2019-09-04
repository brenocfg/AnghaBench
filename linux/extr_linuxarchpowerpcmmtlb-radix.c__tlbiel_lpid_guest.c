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

/* Variables and functions */
 int POWER9_TLB_SETS_RADIX ; 
 unsigned long RIC_FLUSH_PWC ; 
 unsigned long RIC_FLUSH_TLB ; 
 int /*<<< orphan*/  SPRN_LPID ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/  __tlbiel_lpid_guest (unsigned long,int,unsigned long) ; 
 unsigned long mfspr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void _tlbiel_lpid_guest(unsigned long lpid, unsigned long ric)
{
	int set;

	VM_BUG_ON(mfspr(SPRN_LPID) != lpid);

	asm volatile("ptesync": : :"memory");

	/*
	 * Flush the first set of the TLB, and if we're doing a RIC_FLUSH_ALL,
	 * also flush the entire Page Walk Cache.
	 */
	__tlbiel_lpid_guest(lpid, 0, ric);

	/* For PWC, only one flush is needed */
	if (ric == RIC_FLUSH_PWC) {
		asm volatile("ptesync": : :"memory");
		return;
	}

	/* For the remaining sets, just flush the TLB */
	for (set = 1; set < POWER9_TLB_SETS_RADIX ; set++)
		__tlbiel_lpid_guest(lpid, set, RIC_FLUSH_TLB);

	asm volatile("ptesync": : :"memory");
}