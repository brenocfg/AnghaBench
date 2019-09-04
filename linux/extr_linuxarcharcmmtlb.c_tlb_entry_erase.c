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
 unsigned int TLB_DUP_ERR ; 
 unsigned int TLB_LKUP_ERR ; 
 int /*<<< orphan*/  WARN (int,char*,unsigned int) ; 
 int /*<<< orphan*/  __tlb_entry_erase () ; 
 scalar_t__ likely (int) ; 
 unsigned int tlb_entry_lkup (unsigned int) ; 

__attribute__((used)) static void tlb_entry_erase(unsigned int vaddr_n_asid)
{
	unsigned int idx;

	/* Locate the TLB entry for this vaddr + ASID */
	idx = tlb_entry_lkup(vaddr_n_asid);

	/* No error means entry found, zero it out */
	if (likely(!(idx & TLB_LKUP_ERR))) {
		__tlb_entry_erase();
	} else {
		/* Duplicate entry error */
		WARN(idx == TLB_DUP_ERR, "Probe returned Dup PD for %x\n",
					   vaddr_n_asid);
	}
}