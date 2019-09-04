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
struct TYPE_2__ {int /*<<< orphan*/  bad_page_dma; int /*<<< orphan*/  bad_page_cpu; int /*<<< orphan*/  dev; } ;
struct etnaviv_iommuv1_domain {TYPE_1__ base; int /*<<< orphan*/  pgtable_dma; int /*<<< orphan*/  pgtable_cpu; } ;
struct etnaviv_iommu_domain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PT_SIZE ; 
 int /*<<< orphan*/  SZ_4K ; 
 int /*<<< orphan*/  dma_free_wc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct etnaviv_iommuv1_domain*) ; 
 struct etnaviv_iommuv1_domain* to_etnaviv_domain (struct etnaviv_iommu_domain*) ; 

__attribute__((used)) static void etnaviv_iommuv1_domain_free(struct etnaviv_iommu_domain *domain)
{
	struct etnaviv_iommuv1_domain *etnaviv_domain =
			to_etnaviv_domain(domain);

	dma_free_wc(etnaviv_domain->base.dev, PT_SIZE,
		    etnaviv_domain->pgtable_cpu, etnaviv_domain->pgtable_dma);

	dma_free_wc(etnaviv_domain->base.dev, SZ_4K,
		    etnaviv_domain->base.bad_page_cpu,
		    etnaviv_domain->base.bad_page_dma);

	kfree(etnaviv_domain);
}