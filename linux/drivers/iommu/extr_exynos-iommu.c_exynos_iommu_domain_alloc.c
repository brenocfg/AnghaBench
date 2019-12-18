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
typedef  int /*<<< orphan*/  sysmmu_pte_t ;
struct TYPE_2__ {unsigned long aperture_end; int force_aperture; scalar_t__ aperture_start; } ;
struct iommu_domain {TYPE_1__ geometry; } ;
struct exynos_iommu_domain {short* lv2entcnt; struct iommu_domain domain; int /*<<< orphan*/ * pgtable; int /*<<< orphan*/  clients; int /*<<< orphan*/  pgtablelock; int /*<<< orphan*/  lock; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 unsigned int IOMMU_DOMAIN_DMA ; 
 unsigned int IOMMU_DOMAIN_UNMANAGED ; 
 int /*<<< orphan*/  LV1TABLE_SIZE ; 
 int NUM_LV1ENTRIES ; 
 scalar_t__ PG_ENT_SHIFT ; 
 int /*<<< orphan*/  ZERO_LV2LINK ; 
 int __GFP_ZERO ; 
 scalar_t__ __get_free_pages (int,int) ; 
 int /*<<< orphan*/  dma_dev ; 
 scalar_t__ dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int) ; 
 scalar_t__ iommu_get_dma_cookie (struct iommu_domain*) ; 
 int /*<<< orphan*/  iommu_put_dma_cookie (struct iommu_domain*) ; 
 int /*<<< orphan*/  kfree (struct exynos_iommu_domain*) ; 
 struct exynos_iommu_domain* kzalloc (int,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 scalar_t__ virt_to_phys (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct iommu_domain *exynos_iommu_domain_alloc(unsigned type)
{
	struct exynos_iommu_domain *domain;
	dma_addr_t handle;
	int i;

	/* Check if correct PTE offsets are initialized */
	BUG_ON(PG_ENT_SHIFT < 0 || !dma_dev);

	domain = kzalloc(sizeof(*domain), GFP_KERNEL);
	if (!domain)
		return NULL;

	if (type == IOMMU_DOMAIN_DMA) {
		if (iommu_get_dma_cookie(&domain->domain) != 0)
			goto err_pgtable;
	} else if (type != IOMMU_DOMAIN_UNMANAGED) {
		goto err_pgtable;
	}

	domain->pgtable = (sysmmu_pte_t *)__get_free_pages(GFP_KERNEL, 2);
	if (!domain->pgtable)
		goto err_dma_cookie;

	domain->lv2entcnt = (short *)__get_free_pages(GFP_KERNEL | __GFP_ZERO, 1);
	if (!domain->lv2entcnt)
		goto err_counter;

	/* Workaround for System MMU v3.3 to prevent caching 1MiB mapping */
	for (i = 0; i < NUM_LV1ENTRIES; i++)
		domain->pgtable[i] = ZERO_LV2LINK;

	handle = dma_map_single(dma_dev, domain->pgtable, LV1TABLE_SIZE,
				DMA_TO_DEVICE);
	/* For mapping page table entries we rely on dma == phys */
	BUG_ON(handle != virt_to_phys(domain->pgtable));
	if (dma_mapping_error(dma_dev, handle))
		goto err_lv2ent;

	spin_lock_init(&domain->lock);
	spin_lock_init(&domain->pgtablelock);
	INIT_LIST_HEAD(&domain->clients);

	domain->domain.geometry.aperture_start = 0;
	domain->domain.geometry.aperture_end   = ~0UL;
	domain->domain.geometry.force_aperture = true;

	return &domain->domain;

err_lv2ent:
	free_pages((unsigned long)domain->lv2entcnt, 1);
err_counter:
	free_pages((unsigned long)domain->pgtable, 2);
err_dma_cookie:
	if (type == IOMMU_DOMAIN_DMA)
		iommu_put_dma_cookie(&domain->domain);
err_pgtable:
	kfree(domain);
	return NULL;
}