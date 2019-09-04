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
struct ksz_hw {int rx_stop; int rx_cfg; int /*<<< orphan*/  intr_mask; scalar_t__ enabled; } ;

/* Variables and functions */
 int DMA_RX_ENABLE ; 
 int /*<<< orphan*/  KS884X_INT_RX_STOPPED ; 
 int /*<<< orphan*/  hw_start_rx (struct ksz_hw*) ; 

__attribute__((used)) static inline void handle_rx_stop(struct ksz_hw *hw)
{
	/* Receive just has been stopped. */
	if (0 == hw->rx_stop)
		hw->intr_mask &= ~KS884X_INT_RX_STOPPED;
	else if (hw->rx_stop > 1) {
		if (hw->enabled && (hw->rx_cfg & DMA_RX_ENABLE)) {
			hw_start_rx(hw);
		} else {
			hw->intr_mask &= ~KS884X_INT_RX_STOPPED;
			hw->rx_stop = 0;
		}
	} else
		/* Receive just has been started. */
		hw->rx_stop++;
}