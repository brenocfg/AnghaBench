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
typedef  int /*<<< orphan*/  u32 ;
struct imgu_mmu_info {int dummy; } ;
struct imgu_mmu {scalar_t__ base; int /*<<< orphan*/  l1pt; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPU3_ADDR2PTE (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_L1_PHYS ; 
 int /*<<< orphan*/  imgu_mmu_set_halt (struct imgu_mmu*,int) ; 
 int /*<<< orphan*/  imgu_mmu_tlb_invalidate (struct imgu_mmu*) ; 
 struct imgu_mmu* to_imgu_mmu (struct imgu_mmu_info*) ; 
 int /*<<< orphan*/  virt_to_phys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

void imgu_mmu_resume(struct imgu_mmu_info *info)
{
	struct imgu_mmu *mmu = to_imgu_mmu(info);
	u32 pteval;

	imgu_mmu_set_halt(mmu, true);

	pteval = IPU3_ADDR2PTE(virt_to_phys(mmu->l1pt));
	writel(pteval, mmu->base + REG_L1_PHYS);

	imgu_mmu_tlb_invalidate(mmu);
	imgu_mmu_set_halt(mmu, false);
}