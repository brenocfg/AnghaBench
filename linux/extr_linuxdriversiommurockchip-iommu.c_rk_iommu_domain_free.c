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
typedef  int /*<<< orphan*/  u32 ;
struct rk_iommu_domain {int /*<<< orphan*/  domain; int /*<<< orphan*/ * dt; int /*<<< orphan*/  dt_dma; int /*<<< orphan*/  iommus; } ;
struct iommu_domain {scalar_t__ type; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 scalar_t__ IOMMU_DOMAIN_DMA ; 
 int NUM_DT_ENTRIES ; 
 int /*<<< orphan*/  SPAGE_SIZE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dma_dev ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  iommu_put_dma_cookie (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * phys_to_virt (int /*<<< orphan*/ ) ; 
 scalar_t__ rk_dte_is_pt_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rk_dte_pt_address (int /*<<< orphan*/ ) ; 
 struct rk_iommu_domain* to_rk_domain (struct iommu_domain*) ; 

__attribute__((used)) static void rk_iommu_domain_free(struct iommu_domain *domain)
{
	struct rk_iommu_domain *rk_domain = to_rk_domain(domain);
	int i;

	WARN_ON(!list_empty(&rk_domain->iommus));

	for (i = 0; i < NUM_DT_ENTRIES; i++) {
		u32 dte = rk_domain->dt[i];
		if (rk_dte_is_pt_valid(dte)) {
			phys_addr_t pt_phys = rk_dte_pt_address(dte);
			u32 *page_table = phys_to_virt(pt_phys);
			dma_unmap_single(dma_dev, pt_phys,
					 SPAGE_SIZE, DMA_TO_DEVICE);
			free_page((unsigned long)page_table);
		}
	}

	dma_unmap_single(dma_dev, rk_domain->dt_dma,
			 SPAGE_SIZE, DMA_TO_DEVICE);
	free_page((unsigned long)rk_domain->dt);

	if (domain->type == IOMMU_DOMAIN_DMA)
		iommu_put_dma_cookie(&rk_domain->domain);
}