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
typedef  int u64 ;
struct macb_dma_desc_64 {scalar_t__ addrh; } ;
struct macb_dma_desc {int /*<<< orphan*/  addr; } ;
struct macb {int hw_dma_cap; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int HW_DMA_CAP_64B ; 
 int MACB_BF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACB_BFEXT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RX_WADDR ; 
 struct macb_dma_desc_64* macb_64b_desc (struct macb*,struct macb_dma_desc*) ; 

__attribute__((used)) static dma_addr_t macb_get_addr(struct macb *bp, struct macb_dma_desc *desc)
{
	dma_addr_t addr = 0;
#ifdef CONFIG_ARCH_DMA_ADDR_T_64BIT
	struct macb_dma_desc_64 *desc_64;

	if (bp->hw_dma_cap & HW_DMA_CAP_64B) {
		desc_64 = macb_64b_desc(bp, desc);
		addr = ((u64)(desc_64->addrh) << 32);
	}
#endif
	addr |= MACB_BF(RX_WADDR, MACB_BFEXT(RX_WADDR, desc->addr));
	return addr;
}