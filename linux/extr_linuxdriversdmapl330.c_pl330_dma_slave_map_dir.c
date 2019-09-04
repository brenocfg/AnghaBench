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
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int DMA_BIDIRECTIONAL ; 
#define  DMA_DEV_TO_DEV 130 
#define  DMA_DEV_TO_MEM 129 
 int DMA_FROM_DEVICE ; 
#define  DMA_MEM_TO_DEV 128 
 int DMA_NONE ; 
 int DMA_TO_DEVICE ; 

__attribute__((used)) static enum dma_data_direction
pl330_dma_slave_map_dir(enum dma_transfer_direction dir)
{
	switch (dir) {
	case DMA_MEM_TO_DEV:
		return DMA_FROM_DEVICE;
	case DMA_DEV_TO_MEM:
		return DMA_TO_DEVICE;
	case DMA_DEV_TO_DEV:
		return DMA_BIDIRECTIONAL;
	default:
		return DMA_NONE;
	}
}