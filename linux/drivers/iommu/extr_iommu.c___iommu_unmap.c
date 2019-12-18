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
struct iommu_ops {size_t (* unmap ) (struct iommu_domain*,unsigned long,size_t,struct iommu_iotlb_gather*) ;} ;
struct iommu_iotlb_gather {int dummy; } ;
struct iommu_domain {unsigned long pgsize_bitmap; int type; struct iommu_ops* ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ALIGNED (unsigned long,unsigned int) ; 
 int __IOMMU_DOMAIN_PAGING ; 
 int __ffs (unsigned long) ; 
 size_t iommu_pgsize (struct iommu_domain*,unsigned long,size_t) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long,size_t) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned long,size_t,unsigned int) ; 
 size_t stub1 (struct iommu_domain*,unsigned long,size_t,struct iommu_iotlb_gather*) ; 
 int /*<<< orphan*/  trace_unmap (unsigned long,size_t,size_t) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static size_t __iommu_unmap(struct iommu_domain *domain,
			    unsigned long iova, size_t size,
			    struct iommu_iotlb_gather *iotlb_gather)
{
	const struct iommu_ops *ops = domain->ops;
	size_t unmapped_page, unmapped = 0;
	unsigned long orig_iova = iova;
	unsigned int min_pagesz;

	if (unlikely(ops->unmap == NULL ||
		     domain->pgsize_bitmap == 0UL))
		return 0;

	if (unlikely(!(domain->type & __IOMMU_DOMAIN_PAGING)))
		return 0;

	/* find out the minimum page size supported */
	min_pagesz = 1 << __ffs(domain->pgsize_bitmap);

	/*
	 * The virtual address, as well as the size of the mapping, must be
	 * aligned (at least) to the size of the smallest page supported
	 * by the hardware
	 */
	if (!IS_ALIGNED(iova | size, min_pagesz)) {
		pr_err("unaligned: iova 0x%lx size 0x%zx min_pagesz 0x%x\n",
		       iova, size, min_pagesz);
		return 0;
	}

	pr_debug("unmap this: iova 0x%lx size 0x%zx\n", iova, size);

	/*
	 * Keep iterating until we either unmap 'size' bytes (or more)
	 * or we hit an area that isn't mapped.
	 */
	while (unmapped < size) {
		size_t pgsize = iommu_pgsize(domain, iova, size - unmapped);

		unmapped_page = ops->unmap(domain, iova, pgsize, iotlb_gather);
		if (!unmapped_page)
			break;

		pr_debug("unmapped: iova 0x%lx size 0x%zx\n",
			 iova, unmapped_page);

		iova += unmapped_page;
		unmapped += unmapped_page;
	}

	trace_unmap(orig_iova, size, unmapped);
	return unmapped;
}