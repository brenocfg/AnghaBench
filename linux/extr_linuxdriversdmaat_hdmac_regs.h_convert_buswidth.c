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
typedef  int u8 ;
typedef  enum dma_slave_buswidth { ____Placeholder_dma_slave_buswidth } dma_slave_buswidth ;

/* Variables and functions */
#define  DMA_SLAVE_BUSWIDTH_2_BYTES 129 
#define  DMA_SLAVE_BUSWIDTH_4_BYTES 128 

__attribute__((used)) static inline u8 convert_buswidth(enum dma_slave_buswidth addr_width)
{
	switch (addr_width) {
	case DMA_SLAVE_BUSWIDTH_2_BYTES:
		return 1;
	case DMA_SLAVE_BUSWIDTH_4_BYTES:
		return 2;
	default:
		/* For 1 byte width or fallback */
		return 0;
	}
}