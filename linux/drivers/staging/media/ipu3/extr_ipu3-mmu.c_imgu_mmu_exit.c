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
struct imgu_mmu_info {int dummy; } ;
struct imgu_mmu {scalar_t__ dummy_page; int /*<<< orphan*/  dummy_l2pt; int /*<<< orphan*/  l2pts; int /*<<< orphan*/  l1pt; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  imgu_mmu_free_page_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imgu_mmu_set_halt (struct imgu_mmu*,int) ; 
 int /*<<< orphan*/  imgu_mmu_tlb_invalidate (struct imgu_mmu*) ; 
 int /*<<< orphan*/  kfree (struct imgu_mmu*) ; 
 struct imgu_mmu* to_imgu_mmu (struct imgu_mmu_info*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

void imgu_mmu_exit(struct imgu_mmu_info *info)
{
	struct imgu_mmu *mmu = to_imgu_mmu(info);

	/* We are going to free our page tables, no more memory access. */
	imgu_mmu_set_halt(mmu, true);
	imgu_mmu_tlb_invalidate(mmu);

	imgu_mmu_free_page_table(mmu->l1pt);
	vfree(mmu->l2pts);
	imgu_mmu_free_page_table(mmu->dummy_l2pt);
	free_page((unsigned long)mmu->dummy_page);
	kfree(mmu);
}