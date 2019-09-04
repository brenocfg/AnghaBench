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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct ixgbe_mac_addr {int state; int /*<<< orphan*/  pool; int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {int num_rar_entries; } ;
struct ixgbe_hw {TYPE_1__ mac; } ;
struct ixgbe_adapter {struct ixgbe_hw hw; struct ixgbe_mac_addr* mac_table; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int IXGBE_MAC_STATE_IN_USE ; 
 int IXGBE_MAC_STATE_MODIFIED ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 scalar_t__ is_zero_ether_addr (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ixgbe_sync_mac_table (struct ixgbe_adapter*) ; 

int ixgbe_add_mac_filter(struct ixgbe_adapter *adapter,
			 const u8 *addr, u16 pool)
{
	struct ixgbe_mac_addr *mac_table = &adapter->mac_table[0];
	struct ixgbe_hw *hw = &adapter->hw;
	int i;

	if (is_zero_ether_addr(addr))
		return -EINVAL;

	for (i = 0; i < hw->mac.num_rar_entries; i++, mac_table++) {
		if (mac_table->state & IXGBE_MAC_STATE_IN_USE)
			continue;

		ether_addr_copy(mac_table->addr, addr);
		mac_table->pool = pool;

		mac_table->state |= IXGBE_MAC_STATE_MODIFIED |
				    IXGBE_MAC_STATE_IN_USE;

		ixgbe_sync_mac_table(adapter);

		return i;
	}

	return -ENOMEM;
}