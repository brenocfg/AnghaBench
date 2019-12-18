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
struct ixgbe_mac_addr {int state; scalar_t__ pool; } ;
struct TYPE_2__ {int num_rar_entries; } ;
struct ixgbe_hw {TYPE_1__ mac; } ;
struct ixgbe_adapter {struct ixgbe_hw hw; struct ixgbe_mac_addr* mac_table; } ;

/* Variables and functions */
 int IXGBE_MAC_STATE_DEFAULT ; 
 int IXGBE_MAC_STATE_IN_USE ; 

__attribute__((used)) static int ixgbe_available_rars(struct ixgbe_adapter *adapter, u16 pool)
{
	struct ixgbe_mac_addr *mac_table = &adapter->mac_table[0];
	struct ixgbe_hw *hw = &adapter->hw;
	int i, count = 0;

	for (i = 0; i < hw->mac.num_rar_entries; i++, mac_table++) {
		/* do not count default RAR as available */
		if (mac_table->state & IXGBE_MAC_STATE_DEFAULT)
			continue;

		/* only count unused and addresses that belong to us */
		if (mac_table->state & IXGBE_MAC_STATE_IN_USE) {
			if (mac_table->pool != pool)
				continue;
		}

		count++;
	}

	return count;
}