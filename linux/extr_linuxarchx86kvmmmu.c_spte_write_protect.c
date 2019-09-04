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
typedef  int u64 ;

/* Variables and functions */
 int PT_WRITABLE_MASK ; 
 int SPTE_MMU_WRITEABLE ; 
 int /*<<< orphan*/  is_writable_pte (int) ; 
 int mmu_spte_update (int*,int) ; 
 int /*<<< orphan*/  rmap_printk (char*,int*,int) ; 
 scalar_t__ spte_can_locklessly_be_made_writable (int) ; 

__attribute__((used)) static bool spte_write_protect(u64 *sptep, bool pt_protect)
{
	u64 spte = *sptep;

	if (!is_writable_pte(spte) &&
	      !(pt_protect && spte_can_locklessly_be_made_writable(spte)))
		return false;

	rmap_printk("rmap_write_protect: spte %p %llx\n", sptep, *sptep);

	if (pt_protect)
		spte &= ~SPTE_MMU_WRITEABLE;
	spte = spte & ~PT_WRITABLE_MASK;

	return mmu_spte_update(sptep, spte);
}