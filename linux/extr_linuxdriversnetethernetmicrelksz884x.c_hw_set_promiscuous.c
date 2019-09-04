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
typedef  scalar_t__ u8 ;
struct ksz_hw {scalar_t__ enabled; int /*<<< orphan*/  rx_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_RX_PROMISCUOUS ; 
 int /*<<< orphan*/  hw_start_rx (struct ksz_hw*) ; 
 int /*<<< orphan*/  hw_stop_rx (struct ksz_hw*) ; 

__attribute__((used)) static void hw_set_promiscuous(struct ksz_hw *hw, u8 prom)
{
	/* Stop receiving for reconfiguration. */
	hw_stop_rx(hw);

	if (prom)
		hw->rx_cfg |= DMA_RX_PROMISCUOUS;
	else
		hw->rx_cfg &= ~DMA_RX_PROMISCUOUS;

	if (hw->enabled)
		hw_start_rx(hw);
}