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
struct kvaser_pciefd {scalar_t__ reg_base; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int KVASER_PCIEFD_64BIT_DMA_BIT ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 

__attribute__((used)) static void kvaser_pciefd_write_dma_map(struct kvaser_pciefd *pcie,
					dma_addr_t addr, int offset)
{
	u32 word1, word2;

#ifdef CONFIG_ARCH_DMA_ADDR_T_64BIT
	word1 = addr | KVASER_PCIEFD_64BIT_DMA_BIT;
	word2 = addr >> 32;
#else
	word1 = addr;
	word2 = 0;
#endif
	iowrite32(word1, pcie->reg_base + offset);
	iowrite32(word2, pcie->reg_base + offset + 4);
}