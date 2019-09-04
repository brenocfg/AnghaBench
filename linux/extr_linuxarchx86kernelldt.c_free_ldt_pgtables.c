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
struct mm_struct {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void free_ldt_pgtables(struct mm_struct *mm)
{
#ifdef CONFIG_PAGE_TABLE_ISOLATION
	struct mmu_gather tlb;
	unsigned long start = LDT_BASE_ADDR;
	unsigned long end = LDT_END_ADDR;

	if (!static_cpu_has(X86_FEATURE_PTI))
		return;

	tlb_gather_mmu(&tlb, mm, start, end);
	free_pgd_range(&tlb, start, end, start, end);
	tlb_finish_mmu(&tlb, start, end);
#endif
}