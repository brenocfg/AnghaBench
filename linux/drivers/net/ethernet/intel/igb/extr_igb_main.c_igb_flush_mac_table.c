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
struct TYPE_3__ {int rar_entry_count; } ;
struct e1000_hw {TYPE_1__ mac; } ;
struct igb_adapter {TYPE_2__* mac_table; struct e1000_hw hw; } ;
struct TYPE_4__ {scalar_t__ queue; int /*<<< orphan*/  addr; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  IGB_MAC_STATE_IN_USE ; 
 int /*<<< orphan*/  igb_rar_set_index (struct igb_adapter*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void igb_flush_mac_table(struct igb_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	int i;

	for (i = 0; i < hw->mac.rar_entry_count; i++) {
		adapter->mac_table[i].state &= ~IGB_MAC_STATE_IN_USE;
		memset(adapter->mac_table[i].addr, 0, ETH_ALEN);
		adapter->mac_table[i].queue = 0;
		igb_rar_set_index(adapter, i);
	}
}