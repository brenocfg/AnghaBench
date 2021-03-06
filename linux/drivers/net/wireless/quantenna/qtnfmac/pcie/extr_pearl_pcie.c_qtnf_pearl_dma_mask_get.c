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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 

__attribute__((used)) static u64 qtnf_pearl_dma_mask_get(void)
{
#ifdef CONFIG_ARCH_DMA_ADDR_T_64BIT
	return DMA_BIT_MASK(64);
#else
	return DMA_BIT_MASK(32);
#endif
}