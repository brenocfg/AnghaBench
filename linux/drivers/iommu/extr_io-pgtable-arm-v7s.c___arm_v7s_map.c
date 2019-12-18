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
struct io_pgtable_cfg {int dummy; } ;
struct TYPE_2__ {struct io_pgtable_cfg cfg; } ;
struct arm_v7s_io_pgtable {TYPE_1__ iop; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;
typedef  scalar_t__ arm_v7s_iopte ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_V7S_LVL_IDX (unsigned long,int) ; 
 size_t ARM_V7S_LVL_SHIFT (int) ; 
 scalar_t__ ARM_V7S_PTE_IS_TABLE (scalar_t__,int) ; 
 int EEXIST ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ READ_ONCE (scalar_t__) ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__* __arm_v7s_alloc_table (int,int /*<<< orphan*/ ,struct arm_v7s_io_pgtable*) ; 
 int /*<<< orphan*/  __arm_v7s_free_table (scalar_t__*,int,struct arm_v7s_io_pgtable*) ; 
 int /*<<< orphan*/  __arm_v7s_pte_sync (scalar_t__*,int,struct io_pgtable_cfg*) ; 
 int arm_v7s_init_pte (struct arm_v7s_io_pgtable*,unsigned long,int /*<<< orphan*/ ,int,int,int,scalar_t__*) ; 
 scalar_t__ arm_v7s_install_table (scalar_t__*,scalar_t__*,int /*<<< orphan*/ ,struct io_pgtable_cfg*) ; 
 scalar_t__* iopte_deref (scalar_t__,int,struct arm_v7s_io_pgtable*) ; 
 int /*<<< orphan*/  selftest_running ; 

__attribute__((used)) static int __arm_v7s_map(struct arm_v7s_io_pgtable *data, unsigned long iova,
			 phys_addr_t paddr, size_t size, int prot,
			 int lvl, arm_v7s_iopte *ptep)
{
	struct io_pgtable_cfg *cfg = &data->iop.cfg;
	arm_v7s_iopte pte, *cptep;
	int num_entries = size >> ARM_V7S_LVL_SHIFT(lvl);

	/* Find our entry at the current level */
	ptep += ARM_V7S_LVL_IDX(iova, lvl);

	/* If we can install a leaf entry at this level, then do so */
	if (num_entries)
		return arm_v7s_init_pte(data, iova, paddr, prot,
					lvl, num_entries, ptep);

	/* We can't allocate tables at the final level */
	if (WARN_ON(lvl == 2))
		return -EINVAL;

	/* Grab a pointer to the next level */
	pte = READ_ONCE(*ptep);
	if (!pte) {
		cptep = __arm_v7s_alloc_table(lvl + 1, GFP_ATOMIC, data);
		if (!cptep)
			return -ENOMEM;

		pte = arm_v7s_install_table(cptep, ptep, 0, cfg);
		if (pte)
			__arm_v7s_free_table(cptep, lvl + 1, data);
	} else {
		/* We've no easy way of knowing if it's synced yet, so... */
		__arm_v7s_pte_sync(ptep, 1, cfg);
	}

	if (ARM_V7S_PTE_IS_TABLE(pte, lvl)) {
		cptep = iopte_deref(pte, lvl, data);
	} else if (pte) {
		/* We require an unmap first */
		WARN_ON(!selftest_running);
		return -EEXIST;
	}

	/* Rinse, repeat */
	return __arm_v7s_map(data, iova, paddr, size, prot, lvl + 1, cptep);
}