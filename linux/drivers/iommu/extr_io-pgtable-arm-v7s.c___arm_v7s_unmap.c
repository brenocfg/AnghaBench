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
struct iommu_iotlb_gather {int dummy; } ;
struct TYPE_2__ {int quirks; } ;
struct io_pgtable {TYPE_1__ cfg; } ;
struct arm_v7s_io_pgtable {int /*<<< orphan*/  split_lock; struct io_pgtable iop; } ;
typedef  int /*<<< orphan*/  arm_v7s_iopte ;

/* Variables and functions */
 size_t ARM_V7S_BLOCK_SIZE (int) ; 
 int ARM_V7S_CONT_PAGES ; 
 int ARM_V7S_LVL_IDX (unsigned long,int) ; 
 size_t ARM_V7S_LVL_SHIFT (int) ; 
 scalar_t__ ARM_V7S_PTE_IS_TABLE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ARM_V7S_PTE_IS_VALID (int /*<<< orphan*/ ) ; 
 int IO_PGTABLE_QUIRK_NON_STRICT ; 
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  __arm_v7s_free_table (int /*<<< orphan*/ *,int,struct arm_v7s_io_pgtable*) ; 
 int /*<<< orphan*/  __arm_v7s_set_pte (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 scalar_t__ arm_v7s_pte_is_cont (int /*<<< orphan*/ ,int) ; 
 size_t arm_v7s_split_blk_unmap (struct arm_v7s_io_pgtable*,struct iommu_iotlb_gather*,unsigned long,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arm_v7s_split_cont (struct arm_v7s_io_pgtable*,unsigned long,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  io_pgtable_tlb_add_page (struct io_pgtable*,struct iommu_iotlb_gather*,unsigned long,size_t) ; 
 int /*<<< orphan*/  io_pgtable_tlb_flush_walk (struct io_pgtable*,unsigned long,size_t,size_t) ; 
 int /*<<< orphan*/ * iopte_deref (int /*<<< orphan*/ ,int,struct arm_v7s_io_pgtable*) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static size_t __arm_v7s_unmap(struct arm_v7s_io_pgtable *data,
			      struct iommu_iotlb_gather *gather,
			      unsigned long iova, size_t size, int lvl,
			      arm_v7s_iopte *ptep)
{
	arm_v7s_iopte pte[ARM_V7S_CONT_PAGES];
	struct io_pgtable *iop = &data->iop;
	int idx, i = 0, num_entries = size >> ARM_V7S_LVL_SHIFT(lvl);

	/* Something went horribly wrong and we ran out of page table */
	if (WARN_ON(lvl > 2))
		return 0;

	idx = ARM_V7S_LVL_IDX(iova, lvl);
	ptep += idx;
	do {
		pte[i] = READ_ONCE(ptep[i]);
		if (WARN_ON(!ARM_V7S_PTE_IS_VALID(pte[i])))
			return 0;
	} while (++i < num_entries);

	/*
	 * If we've hit a contiguous 'large page' entry at this level, it
	 * needs splitting first, unless we're unmapping the whole lot.
	 *
	 * For splitting, we can't rewrite 16 PTEs atomically, and since we
	 * can't necessarily assume TEX remap we don't have a software bit to
	 * mark live entries being split. In practice (i.e. DMA API code), we
	 * will never be splitting large pages anyway, so just wrap this edge
	 * case in a lock for the sake of correctness and be done with it.
	 */
	if (num_entries <= 1 && arm_v7s_pte_is_cont(pte[0], lvl)) {
		unsigned long flags;

		spin_lock_irqsave(&data->split_lock, flags);
		pte[0] = arm_v7s_split_cont(data, iova, idx, lvl, ptep);
		spin_unlock_irqrestore(&data->split_lock, flags);
	}

	/* If the size matches this level, we're in the right place */
	if (num_entries) {
		size_t blk_size = ARM_V7S_BLOCK_SIZE(lvl);

		__arm_v7s_set_pte(ptep, 0, num_entries, &iop->cfg);

		for (i = 0; i < num_entries; i++) {
			if (ARM_V7S_PTE_IS_TABLE(pte[i], lvl)) {
				/* Also flush any partial walks */
				io_pgtable_tlb_flush_walk(iop, iova, blk_size,
						ARM_V7S_BLOCK_SIZE(lvl + 1));
				ptep = iopte_deref(pte[i], lvl, data);
				__arm_v7s_free_table(ptep, lvl + 1, data);
			} else if (iop->cfg.quirks & IO_PGTABLE_QUIRK_NON_STRICT) {
				/*
				 * Order the PTE update against queueing the IOVA, to
				 * guarantee that a flush callback from a different CPU
				 * has observed it before the TLBIALL can be issued.
				 */
				smp_wmb();
			} else {
				io_pgtable_tlb_add_page(iop, gather, iova, blk_size);
			}
			iova += blk_size;
		}
		return size;
	} else if (lvl == 1 && !ARM_V7S_PTE_IS_TABLE(pte[0], lvl)) {
		/*
		 * Insert a table at the next level to map the old region,
		 * minus the part we want to unmap
		 */
		return arm_v7s_split_blk_unmap(data, gather, iova, size, pte[0],
					       ptep);
	}

	/* Keep on walkin' */
	ptep = iopte_deref(pte[0], lvl, data);
	return __arm_v7s_unmap(data, gather, iova, size, lvl + 1, ptep);
}