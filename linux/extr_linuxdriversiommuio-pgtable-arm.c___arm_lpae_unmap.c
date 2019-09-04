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
struct io_pgtable {int /*<<< orphan*/  cfg; } ;
struct arm_lpae_io_pgtable {struct io_pgtable iop; } ;
typedef  int /*<<< orphan*/  arm_lpae_iopte ;

/* Variables and functions */
 size_t ARM_LPAE_BLOCK_SIZE (int,struct arm_lpae_io_pgtable*) ; 
 size_t ARM_LPAE_GRANULE (struct arm_lpae_io_pgtable*) ; 
 int /*<<< orphan*/  ARM_LPAE_LVL_IDX (unsigned long,int,struct arm_lpae_io_pgtable*) ; 
 int ARM_LPAE_MAX_LEVELS ; 
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  __arm_lpae_free_pgtable (struct arm_lpae_io_pgtable*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __arm_lpae_set_pte (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 size_t arm_lpae_split_blk_unmap (struct arm_lpae_io_pgtable*,unsigned long,size_t,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  io_pgtable_tlb_add_flush (struct io_pgtable*,unsigned long,size_t,size_t,int) ; 
 int /*<<< orphan*/  io_pgtable_tlb_sync (struct io_pgtable*) ; 
 int /*<<< orphan*/ * iopte_deref (int /*<<< orphan*/ ,struct arm_lpae_io_pgtable*) ; 
 scalar_t__ iopte_leaf (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static size_t __arm_lpae_unmap(struct arm_lpae_io_pgtable *data,
			       unsigned long iova, size_t size, int lvl,
			       arm_lpae_iopte *ptep)
{
	arm_lpae_iopte pte;
	struct io_pgtable *iop = &data->iop;

	/* Something went horribly wrong and we ran out of page table */
	if (WARN_ON(lvl == ARM_LPAE_MAX_LEVELS))
		return 0;

	ptep += ARM_LPAE_LVL_IDX(iova, lvl, data);
	pte = READ_ONCE(*ptep);
	if (WARN_ON(!pte))
		return 0;

	/* If the size matches this level, we're in the right place */
	if (size == ARM_LPAE_BLOCK_SIZE(lvl, data)) {
		__arm_lpae_set_pte(ptep, 0, &iop->cfg);

		if (!iopte_leaf(pte, lvl)) {
			/* Also flush any partial walks */
			io_pgtable_tlb_add_flush(iop, iova, size,
						ARM_LPAE_GRANULE(data), false);
			io_pgtable_tlb_sync(iop);
			ptep = iopte_deref(pte, data);
			__arm_lpae_free_pgtable(data, lvl + 1, ptep);
		} else {
			io_pgtable_tlb_add_flush(iop, iova, size, size, true);
		}

		return size;
	} else if (iopte_leaf(pte, lvl)) {
		/*
		 * Insert a table at the next level to map the old region,
		 * minus the part we want to unmap
		 */
		return arm_lpae_split_blk_unmap(data, iova, size, pte,
						lvl + 1, ptep);
	}

	/* Keep on walkin' */
	ptep = iopte_deref(pte, data);
	return __arm_lpae_unmap(data, iova, size, lvl + 1, ptep);
}