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
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 unsigned long DMA_ATTR_PRIVILEGED ; 
#define  DMA_BIDIRECTIONAL 130 
#define  DMA_FROM_DEVICE 129 
#define  DMA_TO_DEVICE 128 
 int IOMMU_CACHE ; 
 int IOMMU_PRIV ; 
 int IOMMU_READ ; 
 int IOMMU_WRITE ; 

int dma_info_to_prot(enum dma_data_direction dir, bool coherent,
		     unsigned long attrs)
{
	int prot = coherent ? IOMMU_CACHE : 0;

	if (attrs & DMA_ATTR_PRIVILEGED)
		prot |= IOMMU_PRIV;

	switch (dir) {
	case DMA_BIDIRECTIONAL:
		return prot | IOMMU_READ | IOMMU_WRITE;
	case DMA_TO_DEVICE:
		return prot | IOMMU_READ;
	case DMA_FROM_DEVICE:
		return prot | IOMMU_WRITE;
	default:
		return 0;
	}
}