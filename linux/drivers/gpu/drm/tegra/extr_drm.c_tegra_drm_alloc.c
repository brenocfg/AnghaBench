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
struct TYPE_2__ {size_t shift; int /*<<< orphan*/  domain; int /*<<< orphan*/  limit; } ;
struct tegra_drm {TYPE_1__ carveout; scalar_t__ domain; } ;
struct iova {int dummy; } ;
typedef  int gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 void* ERR_PTR (int) ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int IOMMU_READ ; 
 int IOMMU_WRITE ; 
 size_t PAGE_ALIGN (size_t) ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  __free_iova (int /*<<< orphan*/ *,struct iova*) ; 
 scalar_t__ __get_free_pages (int,int /*<<< orphan*/ ) ; 
 struct iova* alloc_iova (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (size_t) ; 
 int iommu_map (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int) ; 
 size_t iova_align (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  iova_dma_addr (int /*<<< orphan*/ *,struct iova*) ; 
 int /*<<< orphan*/  virt_to_phys (void*) ; 

void *tegra_drm_alloc(struct tegra_drm *tegra, size_t size, dma_addr_t *dma)
{
	struct iova *alloc;
	void *virt;
	gfp_t gfp;
	int err;

	if (tegra->domain)
		size = iova_align(&tegra->carveout.domain, size);
	else
		size = PAGE_ALIGN(size);

	gfp = GFP_KERNEL | __GFP_ZERO;
	if (!tegra->domain) {
		/*
		 * Many units only support 32-bit addresses, even on 64-bit
		 * SoCs. If there is no IOMMU to translate into a 32-bit IO
		 * virtual address space, force allocations to be in the
		 * lower 32-bit range.
		 */
		gfp |= GFP_DMA;
	}

	virt = (void *)__get_free_pages(gfp, get_order(size));
	if (!virt)
		return ERR_PTR(-ENOMEM);

	if (!tegra->domain) {
		/*
		 * If IOMMU is disabled, devices address physical memory
		 * directly.
		 */
		*dma = virt_to_phys(virt);
		return virt;
	}

	alloc = alloc_iova(&tegra->carveout.domain,
			   size >> tegra->carveout.shift,
			   tegra->carveout.limit, true);
	if (!alloc) {
		err = -EBUSY;
		goto free_pages;
	}

	*dma = iova_dma_addr(&tegra->carveout.domain, alloc);
	err = iommu_map(tegra->domain, *dma, virt_to_phys(virt),
			size, IOMMU_READ | IOMMU_WRITE);
	if (err < 0)
		goto free_iova;

	return virt;

free_iova:
	__free_iova(&tegra->carveout.domain, alloc);
free_pages:
	free_pages((unsigned long)virt, get_order(size));

	return ERR_PTR(err);
}