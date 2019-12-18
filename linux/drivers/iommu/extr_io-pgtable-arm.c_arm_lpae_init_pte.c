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
struct TYPE_2__ {int /*<<< orphan*/  fmt; } ;
struct arm_lpae_io_pgtable {TYPE_1__ iop; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;
typedef  int /*<<< orphan*/  arm_lpae_iopte ;

/* Variables and functions */
 size_t ARM_LPAE_BLOCK_SIZE (int,struct arm_lpae_io_pgtable*) ; 
 int /*<<< orphan*/ * ARM_LPAE_LVL_IDX (unsigned long,int,struct arm_lpae_io_pgtable*) ; 
 scalar_t__ ARM_LPAE_PTE_TYPE_TABLE ; 
 int EEXIST ; 
 int EINVAL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __arm_lpae_init_pte (struct arm_lpae_io_pgtable*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 size_t __arm_lpae_unmap (struct arm_lpae_io_pgtable*,int /*<<< orphan*/ *,unsigned long,size_t,int,int /*<<< orphan*/ *) ; 
 scalar_t__ iopte_leaf (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ iopte_type (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  selftest_running ; 

__attribute__((used)) static int arm_lpae_init_pte(struct arm_lpae_io_pgtable *data,
			     unsigned long iova, phys_addr_t paddr,
			     arm_lpae_iopte prot, int lvl,
			     arm_lpae_iopte *ptep)
{
	arm_lpae_iopte pte = *ptep;

	if (iopte_leaf(pte, lvl, data->iop.fmt)) {
		/* We require an unmap first */
		WARN_ON(!selftest_running);
		return -EEXIST;
	} else if (iopte_type(pte, lvl) == ARM_LPAE_PTE_TYPE_TABLE) {
		/*
		 * We need to unmap and free the old table before
		 * overwriting it with a block entry.
		 */
		arm_lpae_iopte *tblp;
		size_t sz = ARM_LPAE_BLOCK_SIZE(lvl, data);

		tblp = ptep - ARM_LPAE_LVL_IDX(iova, lvl, data);
		if (__arm_lpae_unmap(data, NULL, iova, sz, lvl, tblp) != sz) {
			WARN_ON(1);
			return -EINVAL;
		}
	}

	__arm_lpae_init_pte(data, paddr, prot, lvl, ptep);
	return 0;
}