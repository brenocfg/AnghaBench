#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long u32 ;
struct io_pgtable_ops {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cfg; } ;
struct arm_v7s_io_pgtable {TYPE_1__ iop; int /*<<< orphan*/ * pgd; } ;
typedef  unsigned long phys_addr_t ;
typedef  int /*<<< orphan*/  arm_v7s_iopte ;

/* Variables and functions */
 unsigned long ARM_V7S_CONT_PAGES ; 
 int /*<<< orphan*/  ARM_V7S_LVL_IDX (unsigned long,int) ; 
 unsigned long ARM_V7S_LVL_MASK (int) ; 
 scalar_t__ ARM_V7S_PTE_IS_TABLE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ARM_V7S_PTE_IS_VALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ arm_v7s_pte_is_cont (int /*<<< orphan*/ ,int) ; 
 struct arm_v7s_io_pgtable* io_pgtable_ops_to_data (struct io_pgtable_ops*) ; 
 int /*<<< orphan*/ * iopte_deref (int /*<<< orphan*/ ,int,struct arm_v7s_io_pgtable*) ; 
 unsigned long iopte_to_paddr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

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
		ptep = iopte_deref(pte, lvl, data);
	} while (ARM_V7S_PTE_IS_TABLE(pte, lvl));

	if (!ARM_V7S_PTE_IS_VALID(pte))
		return 0;

	mask = ARM_V7S_LVL_MASK(lvl);
	if (arm_v7s_pte_is_cont(pte, lvl))
		mask *= ARM_V7S_CONT_PAGES;
	return iopte_to_paddr(pte, lvl, &data->iop.cfg) | (iova & ~mask);
}