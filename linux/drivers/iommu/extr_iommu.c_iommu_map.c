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
struct iommu_ops {int (* map ) (struct iommu_domain*,unsigned long,unsigned long,size_t,int) ;int /*<<< orphan*/  (* iotlb_sync_map ) (struct iommu_domain*) ;} ;
struct iommu_domain {unsigned long pgsize_bitmap; int type; struct iommu_ops* ops; } ;
typedef  unsigned long phys_addr_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  IS_ALIGNED (unsigned long,unsigned int) ; 
 int __IOMMU_DOMAIN_PAGING ; 
 int __ffs (unsigned long) ; 
 size_t iommu_pgsize (struct iommu_domain*,unsigned long,size_t) ; 
 int /*<<< orphan*/  iommu_unmap (struct iommu_domain*,unsigned long,size_t) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long,unsigned long*,size_t) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned long,unsigned long*,size_t,unsigned int) ; 
 int stub1 (struct iommu_domain*,unsigned long,unsigned long,size_t,int) ; 
 int /*<<< orphan*/  stub2 (struct iommu_domain*) ; 
 int /*<<< orphan*/  trace_map (unsigned long,unsigned long,size_t) ; 
 scalar_t__ unlikely (int) ; 

int iommu_map(struct iommu_domain *domain, unsigned long iova,
	      phys_addr_t paddr, size_t size, int prot)
{
	const struct iommu_ops *ops = domain->ops;
	unsigned long orig_iova = iova;
	unsigned int min_pagesz;
	size_t orig_size = size;
	phys_addr_t orig_paddr = paddr;
	int ret = 0;

	if (unlikely(ops->map == NULL ||
		     domain->pgsize_bitmap == 0UL))
		return -ENODEV;

	if (unlikely(!(domain->type & __IOMMU_DOMAIN_PAGING)))
		return -EINVAL;

	/* find out the minimum page size supported */
	min_pagesz = 1 << __ffs(domain->pgsize_bitmap);

	/*
	 * both the virtual address and the physical one, as well as
	 * the size of the mapping, must be aligned (at least) to the
	 * size of the smallest page supported by the hardware
	 */
	if (!IS_ALIGNED(iova | paddr | size, min_pagesz)) {
		pr_err("unaligned: iova 0x%lx pa %pa size 0x%zx min_pagesz 0x%x\n",
		       iova, &paddr, size, min_pagesz);
		return -EINVAL;
	}

	pr_debug("map: iova 0x%lx pa %pa size 0x%zx\n", iova, &paddr, size);

	while (size) {
		size_t pgsize = iommu_pgsize(domain, iova | paddr, size);

		pr_debug("mapping: iova 0x%lx pa %pa pgsize 0x%zx\n",
			 iova, &paddr, pgsize);

		ret = ops->map(domain, iova, paddr, pgsize, prot);
		if (ret)
			break;

		iova += pgsize;
		paddr += pgsize;
		size -= pgsize;
	}

	if (ops->iotlb_sync_map)
		ops->iotlb_sync_map(domain);

	/* unroll mapping in case something went wrong */
	if (ret)
		iommu_unmap(domain, orig_iova, orig_size - size);
	else
		trace_map(orig_iova, orig_paddr, orig_size);

	return ret;
}