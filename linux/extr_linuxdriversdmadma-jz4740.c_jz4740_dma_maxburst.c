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
typedef  int u32 ;
typedef  enum jz4740_dma_transfer_size { ____Placeholder_jz4740_dma_transfer_size } jz4740_dma_transfer_size ;

/* Variables and functions */
 int JZ4740_DMA_TRANSFER_SIZE_16BYTE ; 
 int JZ4740_DMA_TRANSFER_SIZE_1BYTE ; 
 int JZ4740_DMA_TRANSFER_SIZE_2BYTE ; 
 int JZ4740_DMA_TRANSFER_SIZE_32BYTE ; 
 int JZ4740_DMA_TRANSFER_SIZE_4BYTE ; 

__attribute__((used)) static enum jz4740_dma_transfer_size jz4740_dma_maxburst(u32 maxburst)
{
	if (maxburst <= 1)
		return JZ4740_DMA_TRANSFER_SIZE_1BYTE;
	else if (maxburst <= 3)
		return JZ4740_DMA_TRANSFER_SIZE_2BYTE;
	else if (maxburst <= 15)
		return JZ4740_DMA_TRANSFER_SIZE_4BYTE;
	else if (maxburst <= 31)
		return JZ4740_DMA_TRANSFER_SIZE_16BYTE;

	return JZ4740_DMA_TRANSFER_SIZE_32BYTE;
}