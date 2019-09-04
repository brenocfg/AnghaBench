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
typedef  unsigned long u32 ;
struct io_pgtable_ops {int dummy; } ;
struct arm_v7s_io_pgtable {unsigned long* pgd; } ;
typedef  unsigned long phys_addr_t ;
typedef  unsigned long arm_v7s_iopte ;

/* Variables and functions */
 unsigned long ARM_V7S_CONT_PAGES ; 
 int /*<<< orphan*/  ARM_V7S_LVL_IDX (unsigned long,int) ; 
 unsigned long ARM_V7S_LVL_MASK (int) ; 
 scalar_t__ ARM_V7S_PTE_IS_TABLE (unsigned long,int) ; 
 int /*<<< orphan*/  ARM_V7S_PTE_IS_VALID (unsigned long) ; 
 unsigned long READ_ONCE (unsigned long) ; 
 scalar_t__ arm_v7s_pte_is_cont (unsigned long,int) ; 
 struct arm_v7s_io_pgtable* io_pgtable_ops_to_data (struct io_pgtable_ops*) ; 
 unsigned long* iopte_deref (unsigned long,int) ; 

__attribute__((used)) static phys_addr_t arm_v7s_iova_to_phys(struct io_pgtable_ops *ops,
					unsigned long iova)
{
	struct arm_v7s_io_pgtable *data = io_pgtable_ops_to_data(ops);
	arm_v7s_iopte *ptep = data->pgd, pte;
	int lvl = 0;
	u32 mask;

	do {
		ptep += ARM_V7S_LVL_IDX(iova, ++lvl);
		pte = READ_ONCE(*ptep);
		ptep = iopte_deref(pte, lvl);
	} while (ARM_V7S_PTE_IS_TABLE(pte, lvl));

	if (!ARM_V7S_PTE_IS_VALID(pte))
		return 0;

	mask = ARM_V7S_LVL_MASK(lvl);
	if (arm_v7s_pte_is_cont(pte, lvl))
		mask *= ARM_V7S_CONT_PAGES;
	return (pte & mask) | (iova & ~mask);
}