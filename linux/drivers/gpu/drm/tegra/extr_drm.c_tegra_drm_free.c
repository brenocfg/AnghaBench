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
struct TYPE_2__ {int /*<<< orphan*/  domain; } ;
struct tegra_drm {TYPE_1__ carveout; scalar_t__ domain; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 size_t PAGE_ALIGN (size_t) ; 
 int /*<<< orphan*/  free_iova (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (size_t) ; 
 int /*<<< orphan*/  iommu_unmap (scalar_t__,int /*<<< orphan*/ ,size_t) ; 
 size_t iova_align (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  iova_pfn (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void tegra_drm_free(struct tegra_drm *tegra, size_t size, void *virt,
		    dma_addr_t dma)
{
	if (tegra->domain)
		size = iova_align(&tegra->carveout.domain, size);
	else
		size = PAGE_ALIGN(size);

	if (tegra->domain) {
		iommu_unmap(tegra->domain, dma, size);
		free_iova(&tegra->carveout.domain,
			  iova_pfn(&tegra->carveout.domain, dma));
	}

	free_pages((unsigned long)virt, get_order(size));
}