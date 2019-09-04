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
struct igb_mac_addr {int state; int /*<<< orphan*/  queue; int /*<<< orphan*/  addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  addr; } ;
struct TYPE_4__ {TYPE_1__ mac; } ;
struct igb_adapter {int /*<<< orphan*/  vfs_allocated_count; TYPE_2__ hw; struct igb_mac_addr* mac_table; } ;

/* Variables and functions */
 int IGB_MAC_STATE_DEFAULT ; 
 int IGB_MAC_STATE_IN_USE ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  igb_rar_set_index (struct igb_adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void igb_set_default_mac_filter(struct igb_adapter *adapter)
{
	struct igb_mac_addr *mac_table = &adapter->mac_table[0];

	ether_addr_copy(mac_table->addr, adapter->hw.mac.addr);
	mac_table->queue = adapter->vfs_allocated_count;
	mac_table->state = IGB_MAC_STATE_DEFAULT | IGB_MAC_STATE_IN_USE;

	igb_rar_set_index(adapter, 0);
}