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
 int DMA_BIDIRECTIONAL ; 
 int DMA_FROM_DEVICE ; 
 int DMA_TO_DEVICE ; 
 int IOMMU_PROT_IR ; 
 int IOMMU_PROT_IW ; 

__attribute__((used)) static int dir2prot(enum dma_data_direction direction)
{
	if (direction == DMA_TO_DEVICE)
		return IOMMU_PROT_IR;
	else if (direction == DMA_FROM_DEVICE)
		return IOMMU_PROT_IW;
	else if (direction == DMA_BIDIRECTIONAL)
		return IOMMU_PROT_IW | IOMMU_PROT_IR;
	else
		return 0;
}