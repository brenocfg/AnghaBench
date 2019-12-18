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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int force_aperture; int /*<<< orphan*/  aperture_end; scalar_t__ aperture_start; } ;
struct iommu_domain {TYPE_1__ geometry; } ;
struct rk_iommu_domain {struct iommu_domain domain; int /*<<< orphan*/ * dt; int /*<<< orphan*/  iommus; int /*<<< orphan*/  dt_lock; int /*<<< orphan*/  iommus_lock; int /*<<< orphan*/  dt_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int GFP_DMA32 ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 unsigned int IOMMU_DOMAIN_DMA ; 
 unsigned int IOMMU_DOMAIN_UNMANAGED ; 
 int /*<<< orphan*/  NUM_DT_ENTRIES ; 
 int /*<<< orphan*/  SPAGE_SIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct rk_iommu_domain* devm_kzalloc (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dma_dev ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 scalar_t__ get_zeroed_page (int) ; 
 scalar_t__ iommu_get_dma_cookie (struct iommu_domain*) ; 
 int /*<<< orphan*/  iommu_put_dma_cookie (struct iommu_domain*) ; 
 int /*<<< orphan*/  rk_table_flush (struct rk_iommu_domain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct iommu_domain *rk_iommu_domain_alloc(unsigned type)
{
	struct rk_iommu_domain *rk_domain;

	if (type != IOMMU_DOMAIN_UNMANAGED && type != IOMMU_DOMAIN_DMA)
		return NULL;

	if (!dma_dev)
		return NULL;

	rk_domain = devm_kzalloc(dma_dev, sizeof(*rk_domain), GFP_KERNEL);
	if (!rk_domain)
		return NULL;

	if (type == IOMMU_DOMAIN_DMA &&
	    iommu_get_dma_cookie(&rk_domain->domain))
		return NULL;

	/*
	 * rk32xx iommus use a 2 level pagetable.
	 * Each level1 (dt) and level2 (pt) table has 1024 4-byte entries.
	 * Allocate one 4 KiB page for each table.
	 */
	rk_domain->dt = (u32 *)get_zeroed_page(GFP_KERNEL | GFP_DMA32);
	if (!rk_domain->dt)
		goto err_put_cookie;

	rk_domain->dt_dma = dma_map_single(dma_dev, rk_domain->dt,
					   SPAGE_SIZE, DMA_TO_DEVICE);
	if (dma_mapping_error(dma_dev, rk_domain->dt_dma)) {
		dev_err(dma_dev, "DMA map error for DT\n");
		goto err_free_dt;
	}

	rk_table_flush(rk_domain, rk_domain->dt_dma, NUM_DT_ENTRIES);

	spin_lock_init(&rk_domain->iommus_lock);
	spin_lock_init(&rk_domain->dt_lock);
	INIT_LIST_HEAD(&rk_domain->iommus);

	rk_domain->domain.geometry.aperture_start = 0;
	rk_domain->domain.geometry.aperture_end   = DMA_BIT_MASK(32);
	rk_domain->domain.geometry.force_aperture = true;

	return &rk_domain->domain;

err_free_dt:
	free_page((unsigned long)rk_domain->dt);
err_put_cookie:
	if (type == IOMMU_DOMAIN_DMA)
		iommu_put_dma_cookie(&rk_domain->domain);

	return NULL;
}