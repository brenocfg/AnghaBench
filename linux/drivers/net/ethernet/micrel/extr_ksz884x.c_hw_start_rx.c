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
struct ksz_hw {int rx_stop; scalar_t__ io; int /*<<< orphan*/  intr_mask; int /*<<< orphan*/  rx_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_START ; 
 int /*<<< orphan*/  KS884X_INT_RX_STOPPED ; 
 scalar_t__ KS_DMA_RX_CTRL ; 
 scalar_t__ KS_DMA_RX_START ; 
 int /*<<< orphan*/  hw_ack_intr (struct ksz_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void hw_start_rx(struct ksz_hw *hw)
{
	writel(hw->rx_cfg, hw->io + KS_DMA_RX_CTRL);

	/* Notify when the receive stops. */
	hw->intr_mask |= KS884X_INT_RX_STOPPED;

	writel(DMA_START, hw->io + KS_DMA_RX_START);
	hw_ack_intr(hw, KS884X_INT_RX_STOPPED);
	hw->rx_stop++;

	/* Variable overflows. */
	if (0 == hw->rx_stop)
		hw->rx_stop = 2;
}