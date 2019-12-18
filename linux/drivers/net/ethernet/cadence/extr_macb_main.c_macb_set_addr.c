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
struct macb_dma_desc_64 {int /*<<< orphan*/  addrh; } ;
struct macb_dma_desc {int /*<<< orphan*/  addr; } ;
struct macb {int hw_dma_cap; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int HW_DMA_CAP_64B ; 
 int /*<<< orphan*/  dma_wmb () ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 struct macb_dma_desc_64* macb_64b_desc (struct macb*,struct macb_dma_desc*) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void macb_set_addr(struct macb *bp, struct macb_dma_desc *desc, dma_addr_t addr)
{
#ifdef CONFIG_ARCH_DMA_ADDR_T_64BIT
	struct macb_dma_desc_64 *desc_64;

	if (bp->hw_dma_cap & HW_DMA_CAP_64B) {
		desc_64 = macb_64b_desc(bp, desc);
		desc_64->addrh = upper_32_bits(addr);
		/* The low bits of RX address contain the RX_USED bit, clearing
		 * of which allows packet RX. Make sure the high bits are also
		 * visible to HW at that point.
		 */
		dma_wmb();
	}
#endif
	desc->addr = lower_32_bits(addr);
}