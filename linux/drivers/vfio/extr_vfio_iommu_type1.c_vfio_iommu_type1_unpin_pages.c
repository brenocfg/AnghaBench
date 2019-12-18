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
struct vfio_iommu {int /*<<< orphan*/  lock; int /*<<< orphan*/  v2; } ;
struct vfio_dma {int dummy; } ;
typedef  unsigned long dma_addr_t ;

/* Variables and functions */
 int EACCES ; 
 int EINVAL ; 
 int /*<<< orphan*/  IS_IOMMU_CAP_DOMAIN_IN_CONTAINER (struct vfio_iommu*) ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct vfio_dma* vfio_find_dma (struct vfio_iommu*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfio_unpin_page_external (struct vfio_dma*,unsigned long,int) ; 

__attribute__((used)) static int vfio_iommu_type1_unpin_pages(void *iommu_data,
					unsigned long *user_pfn,
					int npage)
{
	struct vfio_iommu *iommu = iommu_data;
	bool do_accounting;
	int i;

	if (!iommu || !user_pfn)
		return -EINVAL;

	/* Supported for v2 version only */
	if (!iommu->v2)
		return -EACCES;

	mutex_lock(&iommu->lock);

	do_accounting = !IS_IOMMU_CAP_DOMAIN_IN_CONTAINER(iommu);
	for (i = 0; i < npage; i++) {
		struct vfio_dma *dma;
		dma_addr_t iova;

		iova = user_pfn[i] << PAGE_SHIFT;
		dma = vfio_find_dma(iommu, iova, PAGE_SIZE);
		if (!dma)
			goto unpin_exit;
		vfio_unpin_page_external(dma, iova, do_accounting);
	}

unpin_exit:
	mutex_unlock(&iommu->lock);
	return i > npage ? npage : (i > 0 ? i : -EINVAL);
}