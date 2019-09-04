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
 int DMA_SLAVE_BUSWIDTH_4_BYTES ; 
 int EINVAL ; 

__attribute__((used)) static int convert_buswidth(enum dma_slave_buswidth addr_width)
{
	if (addr_width > DMA_SLAVE_BUSWIDTH_4_BYTES)
		return -EINVAL;

	/* 8 (1 byte) -> 0, 16 (2 bytes) -> 1, 32 (4 bytes) -> 2 */
	return (addr_width >> 1);
}