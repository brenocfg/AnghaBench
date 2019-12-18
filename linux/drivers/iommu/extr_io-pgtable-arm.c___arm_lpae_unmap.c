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
struct io_pgtable {int /*<<< orphan*/  fmt; TYPE_1__ cfg; } ;
struct arm_lpae_io_pgtable {struct io_pgtable iop; } ;
typedef  int /*<<< orphan*/  arm_lpae_iopte ;

/* Variables and functions */
 size_t ARM_LPAE_BLOCK_SIZE (int,struct arm_lpae_io_pgtable*) ; 
 int /*<<< orphan*/  ARM_LPAE_GRANULE (struct arm_lpae_io_pgtable*) ; 
 int /*<<< orphan*/  ARM_LPAE_LVL_IDX (unsigned long,int,struct arm_lpae_io_pgtable*) ; 
 int ARM_LPAE_MAX_LEVELS ; 
 int IO_PGTABLE_QUIRK_NON_STRICT ; 
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  __arm_lpae_free_pgtable (struct arm_lpae_io_pgtable*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __arm_lpae_set_pte (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 size_t arm_lpae_split_blk_unmap (struct arm_lpae_io_pgtable*,struct iommu_iotlb_gather*,unsigned long,size_t,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  io_pgtable_tlb_add_page (struct io_pgtable*,struct iommu_iotlb_gather*,unsigned long,size_t) ; 
 int /*<<< orphan*/  io_pgtable_tlb_flush_walk (struct io_pgtable*,unsigned long,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * iopte_deref (int /*<<< orphan*/ ,struct arm_lpae_io_pgtable*) ; 
 scalar_t__ iopte_leaf (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_wmb () ; 

__attribute__((used)) static size_t __arm_lpae_unmap(struct arm_lpae_io_pgtable *data,
			       struct iommu_iotlb_gather *gather,
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

		if (!iopte_leaf(pte, lvl, iop->fmt)) {
			/* Also flush any partial walks */
			io_pgtable_tlb_flush_walk(iop, iova, size,
						  ARM_LPAE_GRANULE(data));
			ptep = iopte_deref(pte, data);
			__arm_lpae_free_pgtable(data, lvl + 1, ptep);
		} else if (iop->cfg.quirks & IO_PGTABLE_QUIRK_NON_STRICT) {
			/*
			 * Order the PTE update against queueing the IOVA, to
			 * guarantee that a flush callback from a different CPU
			 * has observed it before the TLBIALL can be issued.
			 */
			smp_wmb();
		} else {
			io_pgtable_tlb_add_page(iop, gather, iova, size);
		}

		return size;
	} else if (iopte_leaf(pte, lvl, iop->fmt)) {
		/*
		 * Insert a table at the next level to map the old region,
		 * minus the part we want to unmap
		 */
		return arm_lpae_split_blk_unmap(data, gather, iova, size, pte,
						lvl + 1, ptep);
	}

	/* Keep on walkin' */
	ptep = iopte_deref(pte, data);
	return __arm_lpae_unmap(data, gather, iova, size, lvl + 1, ptep);
}