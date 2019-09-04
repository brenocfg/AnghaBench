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
struct sprd_dma_chn {scalar_t__ chn_base; } ;

/* Variables and functions */
 scalar_t__ SPRD_DMA_CHN_DES_ADDR ; 
 scalar_t__ SPRD_DMA_CHN_WARP_TO ; 
 unsigned long SPRD_DMA_HIGH_ADDR_MASK ; 
 unsigned long SPRD_DMA_HIGH_ADDR_OFFSET ; 
 unsigned long readl (scalar_t__) ; 

__attribute__((used)) static unsigned long sprd_dma_get_dst_addr(struct sprd_dma_chn *schan)
{
	unsigned long addr, addr_high;

	addr = readl(schan->chn_base + SPRD_DMA_CHN_DES_ADDR);
	addr_high = readl(schan->chn_base + SPRD_DMA_CHN_WARP_TO) &
		    SPRD_DMA_HIGH_ADDR_MASK;

	return addr | (addr_high << SPRD_DMA_HIGH_ADDR_OFFSET);
}