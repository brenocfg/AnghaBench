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
struct TYPE_2__ {int /*<<< orphan*/  bad_page_dma; } ;
struct etnaviv_iommuv1_domain {TYPE_1__ base; int /*<<< orphan*/ * pgtable_cpu; } ;
struct etnaviv_iommu_domain {int dummy; } ;

/* Variables and functions */
 size_t EINVAL ; 
 unsigned long GPU_MEM_START ; 
 unsigned long SZ_4K ; 
 struct etnaviv_iommuv1_domain* to_etnaviv_domain (struct etnaviv_iommu_domain*) ; 

__attribute__((used)) static size_t etnaviv_iommuv1_unmap(struct etnaviv_iommu_domain *domain,
	unsigned long iova, size_t size)
{
	struct etnaviv_iommuv1_domain *etnaviv_domain =
			to_etnaviv_domain(domain);
	unsigned int index = (iova - GPU_MEM_START) / SZ_4K;

	if (size != SZ_4K)
		return -EINVAL;

	etnaviv_domain->pgtable_cpu[index] = etnaviv_domain->base.bad_page_dma;

	return SZ_4K;
}