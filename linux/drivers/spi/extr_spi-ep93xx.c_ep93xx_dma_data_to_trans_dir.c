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
 int DMA_DEV_TO_MEM ; 
#define  DMA_FROM_DEVICE 129 
 int DMA_MEM_TO_DEV ; 
#define  DMA_TO_DEVICE 128 
 int DMA_TRANS_NONE ; 

__attribute__((used)) static enum dma_transfer_direction
ep93xx_dma_data_to_trans_dir(enum dma_data_direction dir)
{
	switch (dir) {
	case DMA_TO_DEVICE:
		return DMA_MEM_TO_DEV;
	case DMA_FROM_DEVICE:
		return DMA_DEV_TO_MEM;
	default:
		return DMA_TRANS_NONE;
	}
}