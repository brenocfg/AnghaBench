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
struct etnaviv_iommu_domain {TYPE_1__* ops; } ;
struct TYPE_2__ {size_t (* unmap ) (struct etnaviv_iommu_domain*,unsigned long,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ALIGNED (unsigned long,size_t) ; 
 size_t SZ_4K ; 
 int /*<<< orphan*/  pr_err (char*,unsigned long,size_t,size_t) ; 
 size_t stub1 (struct etnaviv_iommu_domain*,unsigned long,size_t) ; 

__attribute__((used)) static void etnaviv_domain_unmap(struct etnaviv_iommu_domain *domain,
				 unsigned long iova, size_t size)
{
	size_t unmapped_page, unmapped = 0;
	size_t pgsize = SZ_4K;

	if (!IS_ALIGNED(iova | size, pgsize)) {
		pr_err("unaligned: iova 0x%lx size 0x%zx min_pagesz 0x%zx\n",
		       iova, size, pgsize);
		return;
	}

	while (unmapped < size) {
		unmapped_page = domain->ops->unmap(domain, iova, pgsize);
		if (!unmapped_page)
			break;

		iova += unmapped_page;
		unmapped += unmapped_page;
	}
}