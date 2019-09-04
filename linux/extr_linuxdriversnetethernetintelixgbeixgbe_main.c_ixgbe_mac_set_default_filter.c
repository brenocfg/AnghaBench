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
struct TYPE_3__ {int /*<<< orphan*/  (* set_rar ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {TYPE_1__ ops; int /*<<< orphan*/  addr; } ;
struct ixgbe_hw {TYPE_2__ mac; } ;
struct ixgbe_adapter {struct ixgbe_hw hw; struct ixgbe_mac_addr* mac_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int IXGBE_MAC_STATE_DEFAULT ; 
 int IXGBE_MAC_STATE_IN_USE ; 
 int /*<<< orphan*/  IXGBE_RAH_AV ; 
 int /*<<< orphan*/  VMDQ_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ixgbe_mac_set_default_filter(struct ixgbe_adapter *adapter)
{
	struct ixgbe_mac_addr *mac_table = &adapter->mac_table[0];
	struct ixgbe_hw *hw = &adapter->hw;

	memcpy(&mac_table->addr, hw->mac.addr, ETH_ALEN);
	mac_table->pool = VMDQ_P(0);

	mac_table->state = IXGBE_MAC_STATE_DEFAULT | IXGBE_MAC_STATE_IN_USE;

	hw->mac.ops.set_rar(hw, 0, mac_table->addr, mac_table->pool,
			    IXGBE_RAH_AV);
}