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
struct page {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  IOMMU_MAPPING_ERROR ; 
 int PAGE_ALIGN (size_t) ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  __iommu_dma_free_pages (struct page**,int) ; 
 int /*<<< orphan*/  __iommu_dma_unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  iommu_get_domain_for_dev (struct device*) ; 

void iommu_dma_free(struct device *dev, struct page **pages, size_t size,
		dma_addr_t *handle)
{
	__iommu_dma_unmap(iommu_get_domain_for_dev(dev), *handle, size);
	__iommu_dma_free_pages(pages, PAGE_ALIGN(size) >> PAGE_SHIFT);
	*handle = IOMMU_MAPPING_ERROR;
}