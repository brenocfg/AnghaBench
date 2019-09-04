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
typedef  enum dma_slave_buswidth { ____Placeholder_dma_slave_buswidth } dma_slave_buswidth ;

/* Variables and functions */
#define  DMA_SLAVE_BUSWIDTH_1_BYTE 131 
#define  DMA_SLAVE_BUSWIDTH_2_BYTES 130 
#define  DMA_SLAVE_BUSWIDTH_4_BYTES 129 
#define  DMA_SLAVE_BUSWIDTH_8_BYTES 128 
 int EINVAL ; 

__attribute__((used)) static int sprd_dma_get_step(enum dma_slave_buswidth buswidth)
{
	switch (buswidth) {
	case DMA_SLAVE_BUSWIDTH_1_BYTE:
	case DMA_SLAVE_BUSWIDTH_2_BYTES:
	case DMA_SLAVE_BUSWIDTH_4_BYTES:
	case DMA_SLAVE_BUSWIDTH_8_BYTES:
		return buswidth;

	default:
		return -EINVAL;
	}
}