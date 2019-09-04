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
struct mmu_gather {int dummy; } ;

/* Variables and functions */
 scalar_t__ REGION_NUMBER (unsigned long) ; 
 scalar_t__ RGN_HPAGE ; 
 int /*<<< orphan*/  free_pgd_range (struct mmu_gather*,unsigned long,unsigned long,unsigned long,unsigned long) ; 
 unsigned long htlbpage_to_page (unsigned long) ; 

void hugetlb_free_pgd_range(struct mmu_gather *tlb,
			unsigned long addr, unsigned long end,
			unsigned long floor, unsigned long ceiling)
{
	/*
	 * This is called to free hugetlb page tables.
	 *
	 * The offset of these addresses from the base of the hugetlb
	 * region must be scaled down by HPAGE_SIZE/PAGE_SIZE so that
	 * the standard free_pgd_range will free the right page tables.
	 *
	 * If floor and ceiling are also in the hugetlb region, they
	 * must likewise be scaled down; but if outside, left unchanged.
	 */

	addr = htlbpage_to_page(addr);
	end  = htlbpage_to_page(end);
	if (REGION_NUMBER(floor) == RGN_HPAGE)
		floor = htlbpage_to_page(floor);
	if (REGION_NUMBER(ceiling) == RGN_HPAGE)
		ceiling = htlbpage_to_page(ceiling);

	free_pgd_range(tlb, addr, end, floor, ceiling);
}