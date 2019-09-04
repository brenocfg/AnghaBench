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
struct TYPE_2__ {size_t granule; } ;
struct iommu_dma_cookie {scalar_t__ type; TYPE_1__ iovad; } ;

/* Variables and functions */
 scalar_t__ IOMMU_DMA_IOVA_COOKIE ; 
 size_t PAGE_SIZE ; 

__attribute__((used)) static inline size_t cookie_msi_granule(struct iommu_dma_cookie *cookie)
{
	if (cookie->type == IOMMU_DMA_IOVA_COOKIE)
		return cookie->iovad.granule;
	return PAGE_SIZE;
}