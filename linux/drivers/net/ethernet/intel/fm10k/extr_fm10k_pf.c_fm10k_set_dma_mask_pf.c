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
typedef  int /*<<< orphan*/  u32 ;
struct fm10k_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_PHYADDR ; 
 int /*<<< orphan*/  fm10k_write_reg (struct fm10k_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fm10k_set_dma_mask_pf(struct fm10k_hw *hw, u64 dma_mask)
{
	/* we need to write the upper 32 bits of DMA mask to PhyAddrSpace */
	u32 phyaddr = (u32)(dma_mask >> 32);

	fm10k_write_reg(hw, FM10K_PHYADDR, phyaddr);
}