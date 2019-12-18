#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct TYPE_2__ {unsigned long rx_ok; unsigned long tx_ok; } ;
struct atl1e_adapter {int /*<<< orphan*/  hw; TYPE_1__ hw_stats; } ;

/* Variables and functions */
 scalar_t__ AT_READ_REG (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ REG_MAC_RX_STATUS_BIN ; 
 scalar_t__ REG_MAC_RX_STATUS_END ; 
 scalar_t__ REG_MAC_TX_STATUS_BIN ; 
 scalar_t__ REG_MAC_TX_STATUS_END ; 

__attribute__((used)) static void atl1e_update_hw_stats(struct atl1e_adapter *adapter)
{
	u16 hw_reg_addr = 0;
	unsigned long *stats_item = NULL;

	/* update rx status */
	hw_reg_addr = REG_MAC_RX_STATUS_BIN;
	stats_item  = &adapter->hw_stats.rx_ok;
	while (hw_reg_addr <= REG_MAC_RX_STATUS_END) {
		*stats_item += AT_READ_REG(&adapter->hw, hw_reg_addr);
		stats_item++;
		hw_reg_addr += 4;
	}
	/* update tx status */
	hw_reg_addr = REG_MAC_TX_STATUS_BIN;
	stats_item  = &adapter->hw_stats.tx_ok;
	while (hw_reg_addr <= REG_MAC_TX_STATUS_END) {
		*stats_item += AT_READ_REG(&adapter->hw, hw_reg_addr);
		stats_item++;
		hw_reg_addr += 4;
	}
}