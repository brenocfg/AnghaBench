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
struct iova_domain {int dummy; } ;
struct iommu_dma_cookie {scalar_t__ type; size_t msi_iova; scalar_t__ fq_domain; struct iova_domain iovad; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 scalar_t__ IOMMU_DMA_MSI_COOKIE ; 
 int /*<<< orphan*/  free_iova_fast (struct iova_domain*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  iova_pfn (struct iova_domain*,int /*<<< orphan*/ ) ; 
 size_t iova_shift (struct iova_domain*) ; 
 int /*<<< orphan*/  queue_iova (struct iova_domain*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iommu_dma_free_iova(struct iommu_dma_cookie *cookie,
		dma_addr_t iova, size_t size)
{
	struct iova_domain *iovad = &cookie->iovad;

	/* The MSI case is only ever cleaning up its most recent allocation */
	if (cookie->type == IOMMU_DMA_MSI_COOKIE)
		cookie->msi_iova -= size;
	else if (cookie->fq_domain)	/* non-strict mode */
		queue_iova(iovad, iova_pfn(iovad, iova),
				size >> iova_shift(iovad), 0);
	else
		free_iova_fast(iovad, iova_pfn(iovad, iova),
				size >> iova_shift(iovad));
}