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
 size_t ARM_V7S_BLOCK_SIZE (int) ; 
 scalar_t__* ARM_V7S_LVL_IDX (unsigned long,int) ; 
 scalar_t__ ARM_V7S_PTE_IS_TABLE (scalar_t__,int) ; 
 int EEXIST ; 
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  __arm_v7s_set_pte (scalar_t__*,scalar_t__,int,struct io_pgtable_cfg*) ; 
 size_t __arm_v7s_unmap (struct arm_v7s_io_pgtable*,int /*<<< orphan*/ *,unsigned long,size_t,int,scalar_t__*) ; 
 scalar_t__ arm_v7s_prot_to_pte (int,int,struct io_pgtable_cfg*) ; 
 scalar_t__ arm_v7s_pte_to_cont (scalar_t__,int) ; 
 scalar_t__ paddr_to_iopte (int /*<<< orphan*/ ,int,struct io_pgtable_cfg*) ; 
 int /*<<< orphan*/  selftest_running ; 

__attribute__((used)) static int arm_v7s_init_pte(struct arm_v7s_io_pgtable *data,
			    unsigned long iova, phys_addr_t paddr, int prot,
			    int lvl, int num_entries, arm_v7s_iopte *ptep)
{
	struct io_pgtable_cfg *cfg = &data->iop.cfg;
	arm_v7s_iopte pte;
	int i;

	for (i = 0; i < num_entries; i++)
		if (ARM_V7S_PTE_IS_TABLE(ptep[i], lvl)) {
			/*
			 * We need to unmap and free the old table before
			 * overwriting it with a block entry.
			 */
			arm_v7s_iopte *tblp;
			size_t sz = ARM_V7S_BLOCK_SIZE(lvl);

			tblp = ptep - ARM_V7S_LVL_IDX(iova, lvl);
			if (WARN_ON(__arm_v7s_unmap(data, NULL, iova + i * sz,
						    sz, lvl, tblp) != sz))
				return -EINVAL;
		} else if (ptep[i]) {
			/* We require an unmap first */
			WARN_ON(!selftest_running);
			return -EEXIST;
		}

	pte = arm_v7s_prot_to_pte(prot, lvl, cfg);
	if (num_entries > 1)
		pte = arm_v7s_pte_to_cont(pte, lvl);

	pte |= paddr_to_iopte(paddr, lvl, cfg);

	__arm_v7s_set_pte(ptep, pte, num_entries, cfg);
	return 0;
}