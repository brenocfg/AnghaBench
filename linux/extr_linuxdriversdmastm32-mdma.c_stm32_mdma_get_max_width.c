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
typedef  enum dma_slave_buswidth { ____Placeholder_dma_slave_buswidth } dma_slave_buswidth ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int DMA_SLAVE_BUSWIDTH_1_BYTE ; 
 int DMA_SLAVE_BUSWIDTH_8_BYTES ; 

__attribute__((used)) static enum dma_slave_buswidth stm32_mdma_get_max_width(dma_addr_t addr,
							u32 buf_len, u32 tlen)
{
	enum dma_slave_buswidth max_width = DMA_SLAVE_BUSWIDTH_8_BYTES;

	for (max_width = DMA_SLAVE_BUSWIDTH_8_BYTES;
	     max_width > DMA_SLAVE_BUSWIDTH_1_BYTE;
	     max_width >>= 1) {
		/*
		 * Address and buffer length both have to be aligned on
		 * bus width
		 */
		if ((((buf_len | addr) & (max_width - 1)) == 0) &&
		    tlen >= max_width)
			break;
	}

	return max_width;
}