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
struct ixgbe_mac_addr {int /*<<< orphan*/  state; } ;
struct TYPE_2__ {int num_rar_entries; } ;
struct ixgbe_hw {TYPE_1__ mac; } ;
struct ixgbe_adapter {struct ixgbe_hw hw; struct ixgbe_mac_addr* mac_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_MAC_STATE_IN_USE ; 
 int /*<<< orphan*/  IXGBE_MAC_STATE_MODIFIED ; 
 int /*<<< orphan*/  ixgbe_sync_mac_table (struct ixgbe_adapter*) ; 

__attribute__((used)) static void ixgbe_flush_sw_mac_table(struct ixgbe_adapter *adapter)
{
	struct ixgbe_mac_addr *mac_table = &adapter->mac_table[0];
	struct ixgbe_hw *hw = &adapter->hw;
	int i;

	for (i = 0; i < hw->mac.num_rar_entries; i++, mac_table++) {
		mac_table->state |= IXGBE_MAC_STATE_MODIFIED;
		mac_table->state &= ~IXGBE_MAC_STATE_IN_USE;
	}

	ixgbe_sync_mac_table(adapter);
}