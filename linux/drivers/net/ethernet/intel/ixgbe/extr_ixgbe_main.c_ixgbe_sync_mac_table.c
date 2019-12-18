#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ixgbe_mac_addr {int state; int /*<<< orphan*/  pool; int /*<<< orphan*/  addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* clear_rar ) (struct ixgbe_hw*,int) ;int /*<<< orphan*/  (* set_rar ) (struct ixgbe_hw*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int num_rar_entries; TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ mac; } ;
struct ixgbe_adapter {struct ixgbe_hw hw; struct ixgbe_mac_addr* mac_table; } ;

/* Variables and functions */
 int IXGBE_MAC_STATE_IN_USE ; 
 int IXGBE_MAC_STATE_MODIFIED ; 
 int /*<<< orphan*/  IXGBE_RAH_AV ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct ixgbe_hw*,int) ; 

__attribute__((used)) static void ixgbe_sync_mac_table(struct ixgbe_adapter *adapter)
{
	struct ixgbe_mac_addr *mac_table = &adapter->mac_table[0];
	struct ixgbe_hw *hw = &adapter->hw;
	int i;

	for (i = 0; i < hw->mac.num_rar_entries; i++, mac_table++) {
		if (!(mac_table->state & IXGBE_MAC_STATE_MODIFIED))
			continue;

		mac_table->state &= ~IXGBE_MAC_STATE_MODIFIED;

		if (mac_table->state & IXGBE_MAC_STATE_IN_USE)
			hw->mac.ops.set_rar(hw, i,
					    mac_table->addr,
					    mac_table->pool,
					    IXGBE_RAH_AV);
		else
			hw->mac.ops.clear_rar(hw, i);
	}
}