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
typedef  scalar_t__ u32 ;
typedef  enum dma_slave_buswidth { ____Placeholder_dma_slave_buswidth } dma_slave_buswidth ;

/* Variables and functions */
 int DMA_SLAVE_BUSWIDTH_1_BYTE ; 
 int DMA_SLAVE_BUSWIDTH_2_BYTES ; 
 int DMA_SLAVE_BUSWIDTH_4_BYTES ; 
 scalar_t__ STM32_DMA_FIFO_THRESHOLD_FULL ; 

__attribute__((used)) static enum dma_slave_buswidth stm32_dma_get_max_width(u32 buf_len,
						       u32 threshold)
{
	enum dma_slave_buswidth max_width;

	if (threshold == STM32_DMA_FIFO_THRESHOLD_FULL)
		max_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	else
		max_width = DMA_SLAVE_BUSWIDTH_2_BYTES;

	while ((buf_len < max_width  || buf_len % max_width) &&
	       max_width > DMA_SLAVE_BUSWIDTH_1_BYTE)
		max_width = max_width >> 1;

	return max_width;
}