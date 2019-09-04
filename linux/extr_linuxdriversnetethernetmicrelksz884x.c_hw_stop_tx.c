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
struct ksz_hw {int tx_cfg; scalar_t__ io; } ;

/* Variables and functions */
 int DMA_TX_ENABLE ; 
 scalar_t__ KS_DMA_TX_CTRL ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void hw_stop_tx(struct ksz_hw *hw)
{
	writel((hw->tx_cfg & ~DMA_TX_ENABLE), hw->io + KS_DMA_TX_CTRL);
}