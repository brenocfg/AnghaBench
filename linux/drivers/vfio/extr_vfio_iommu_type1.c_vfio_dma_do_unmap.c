#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct vfio_iommu_type1_dma_unmap {int iova; int size; } ;
struct vfio_iommu {int /*<<< orphan*/  lock; int /*<<< orphan*/  notifier; scalar_t__ v2; } ;
struct vfio_dma {scalar_t__ iova; scalar_t__ size; int /*<<< orphan*/  pfn_list; TYPE_1__* task; } ;
struct TYPE_4__ {scalar_t__ mm; } ;
struct TYPE_3__ {scalar_t__ mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 int PAGE_MASK ; 
 int /*<<< orphan*/  RB_EMPTY_ROOT (int /*<<< orphan*/ *) ; 
 int SIZE_MAX ; 
 int /*<<< orphan*/  VFIO_IOMMU_NOTIFY_DMA_UNMAP ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int __ffs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blocking_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct vfio_iommu_type1_dma_unmap*) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct vfio_dma* vfio_find_dma (struct vfio_iommu*,int,int) ; 
 int /*<<< orphan*/  vfio_pgsize_bitmap (struct vfio_iommu*) ; 
 int /*<<< orphan*/  vfio_remove_dma (struct vfio_iommu*,struct vfio_dma*) ; 

__attribute__((used)) static int vfio_dma_do_unmap(struct vfio_iommu *iommu,
			     struct vfio_iommu_type1_dma_unmap *unmap)
{
	uint64_t mask;
	struct vfio_dma *dma, *dma_last = NULL;
	size_t unmapped = 0;
	int ret = 0, retries = 0;

	mask = ((uint64_t)1 << __ffs(vfio_pgsize_bitmap(iommu))) - 1;

	if (unmap->iova & mask)
		return -EINVAL;
	if (!unmap->size || unmap->size & mask)
		return -EINVAL;
	if (unmap->iova + unmap->size - 1 < unmap->iova ||
	    unmap->size > SIZE_MAX)
		return -EINVAL;

	WARN_ON(mask & PAGE_MASK);
again:
	mutex_lock(&iommu->lock);

	/*
	 * vfio-iommu-type1 (v1) - User mappings were coalesced together to
	 * avoid tracking individual mappings.  This means that the granularity
	 * of the original mapping was lost and the user was allowed to attempt
	 * to unmap any range.  Depending on the contiguousness of physical
	 * memory and page sizes supported by the IOMMU, arbitrary unmaps may
	 * or may not have worked.  We only guaranteed unmap granularity
	 * matching the original mapping; even though it was untracked here,
	 * the original mappings are reflected in IOMMU mappings.  This
	 * resulted in a couple unusual behaviors.  First, if a range is not
	 * able to be unmapped, ex. a set of 4k pages that was mapped as a
	 * 2M hugepage into the IOMMU, the unmap ioctl returns success but with
	 * a zero sized unmap.  Also, if an unmap request overlaps the first
	 * address of a hugepage, the IOMMU will unmap the entire hugepage.
	 * This also returns success and the returned unmap size reflects the
	 * actual size unmapped.
	 *
	 * We attempt to maintain compatibility with this "v1" interface, but
	 * we take control out of the hands of the IOMMU.  Therefore, an unmap
	 * request offset from the beginning of the original mapping will
	 * return success with zero sized unmap.  And an unmap request covering
	 * the first iova of mapping will unmap the entire range.
	 *
	 * The v2 version of this interface intends to be more deterministic.
	 * Unmap requests must fully cover previous mappings.  Multiple
	 * mappings may still be unmaped by specifying large ranges, but there
	 * must not be any previous mappings bisected by the range.  An error
	 * will be returned if these conditions are not met.  The v2 interface
	 * will only return success and a size of zero if there were no
	 * mappings within the range.
	 */
	if (iommu->v2) {
		dma = vfio_find_dma(iommu, unmap->iova, 1);
		if (dma && dma->iova != unmap->iova) {
			ret = -EINVAL;
			goto unlock;
		}
		dma = vfio_find_dma(iommu, unmap->iova + unmap->size - 1, 0);
		if (dma && dma->iova + dma->size != unmap->iova + unmap->size) {
			ret = -EINVAL;
			goto unlock;
		}
	}

	while ((dma = vfio_find_dma(iommu, unmap->iova, unmap->size))) {
		if (!iommu->v2 && unmap->iova > dma->iova)
			break;
		/*
		 * Task with same address space who mapped this iova range is
		 * allowed to unmap the iova range.
		 */
		if (dma->task->mm != current->mm)
			break;

		if (!RB_EMPTY_ROOT(&dma->pfn_list)) {
			struct vfio_iommu_type1_dma_unmap nb_unmap;

			if (dma_last == dma) {
				BUG_ON(++retries > 10);
			} else {
				dma_last = dma;
				retries = 0;
			}

			nb_unmap.iova = dma->iova;
			nb_unmap.size = dma->size;

			/*
			 * Notify anyone (mdev vendor drivers) to invalidate and
			 * unmap iovas within the range we're about to unmap.
			 * Vendor drivers MUST unpin pages in response to an
			 * invalidation.
			 */
			mutex_unlock(&iommu->lock);
			blocking_notifier_call_chain(&iommu->notifier,
						    VFIO_IOMMU_NOTIFY_DMA_UNMAP,
						    &nb_unmap);
			goto again;
		}
		unmapped += dma->size;
		vfio_remove_dma(iommu, dma);
	}

unlock:
	mutex_unlock(&iommu->lock);

	/* Report how much was unmapped */
	unmap->size = unmapped;

	return ret;
}