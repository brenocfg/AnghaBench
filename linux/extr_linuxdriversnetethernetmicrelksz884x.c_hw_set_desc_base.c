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
struct ksz_hw {scalar_t__ io; } ;

/* Variables and functions */
 scalar_t__ KS_DMA_RX_ADDR ; 
 scalar_t__ KS_DMA_TX_ADDR ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void hw_set_desc_base(struct ksz_hw *hw, u32 tx_addr, u32 rx_addr)
{
	/* Set base address of Tx/Rx descriptors. */
	writel(tx_addr, hw->io + KS_DMA_TX_ADDR);
	writel(rx_addr, hw->io + KS_DMA_RX_ADDR);
}