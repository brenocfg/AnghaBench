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
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  bad_page_dma; scalar_t__ bad_page_cpu; } ;
struct etnaviv_iommuv2_domain {int /*<<< orphan*/ * stlb_dma; scalar_t__* stlb_cpu; TYPE_1__ base; int /*<<< orphan*/  mtlb_dma; scalar_t__ mtlb_cpu; int /*<<< orphan*/  pta_dma; scalar_t__ pta_cpu; } ;
struct etnaviv_iommu_domain {int dummy; } ;

/* Variables and functions */
 int MMUv2_MAX_STLB_ENTRIES ; 
 int /*<<< orphan*/  SZ_4K ; 
 int /*<<< orphan*/  dma_free_wc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct etnaviv_iommuv2_domain* to_etnaviv_domain (struct etnaviv_iommu_domain*) ; 
 int /*<<< orphan*/  vfree (struct etnaviv_iommuv2_domain*) ; 

__attribute__((used)) static void etnaviv_iommuv2_domain_free(struct etnaviv_iommu_domain *domain)
{
	struct etnaviv_iommuv2_domain *etnaviv_domain =
			to_etnaviv_domain(domain);
	int i;

	dma_free_wc(etnaviv_domain->base.dev, SZ_4K,
		    etnaviv_domain->base.bad_page_cpu,
		    etnaviv_domain->base.bad_page_dma);

	dma_free_wc(etnaviv_domain->base.dev, SZ_4K,
		    etnaviv_domain->pta_cpu, etnaviv_domain->pta_dma);

	dma_free_wc(etnaviv_domain->base.dev, SZ_4K,
		    etnaviv_domain->mtlb_cpu, etnaviv_domain->mtlb_dma);

	for (i = 0; i < MMUv2_MAX_STLB_ENTRIES; i++) {
		if (etnaviv_domain->stlb_cpu[i])
			dma_free_wc(etnaviv_domain->base.dev, SZ_4K,
				    etnaviv_domain->stlb_cpu[i],
				    etnaviv_domain->stlb_dma[i]);
	}

	vfree(etnaviv_domain);
}