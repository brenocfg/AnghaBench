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
typedef  int /*<<< orphan*/  u32 ;
struct mv_xor_desc_slot {struct mv_xor_desc* hw_desc; } ;
struct mv_xor_desc {int /*<<< orphan*/  byte_count; int /*<<< orphan*/  phy_dest_addr; int /*<<< orphan*/  desc_command; scalar_t__ phy_next_desc; int /*<<< orphan*/  status; } ;
typedef  enum dma_ctrl_flags { ____Placeholder_dma_ctrl_flags } dma_ctrl_flags ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int DMA_PREP_INTERRUPT ; 
 int /*<<< orphan*/  XOR_DESC_DMA_OWNED ; 
 int /*<<< orphan*/  XOR_DESC_EOD_INT_EN ; 

__attribute__((used)) static void mv_desc_init(struct mv_xor_desc_slot *desc,
			 dma_addr_t addr, u32 byte_count,
			 enum dma_ctrl_flags flags)
{
	struct mv_xor_desc *hw_desc = desc->hw_desc;

	hw_desc->status = XOR_DESC_DMA_OWNED;
	hw_desc->phy_next_desc = 0;
	/* Enable end-of-descriptor interrupts only for DMA_PREP_INTERRUPT */
	hw_desc->desc_command = (flags & DMA_PREP_INTERRUPT) ?
				XOR_DESC_EOD_INT_EN : 0;
	hw_desc->phy_dest_addr = addr;
	hw_desc->byte_count = byte_count;
}