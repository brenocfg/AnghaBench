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
typedef  int dma_addr_t ;

/* Variables and functions */
 size_t LLI_WORD0_OFFSET ; 
 int U32_MAX ; 

__attribute__((used)) static inline void cc_lli_set_addr(u32 *lli_p, dma_addr_t addr)
{
	lli_p[LLI_WORD0_OFFSET] = (addr & U32_MAX);
#ifdef CONFIG_ARCH_DMA_ADDR_T_64BIT
	lli_p[LLI_WORD1_OFFSET] &= ~LLI_HADDR_MASK;
	lli_p[LLI_WORD1_OFFSET] |= FIELD_PREP(LLI_HADDR_MASK, (addr >> 32));
#endif /* CONFIG_ARCH_DMA_ADDR_T_64BIT */
}