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
struct igc_mac_addr {int state; int /*<<< orphan*/  addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  addr; } ;
struct TYPE_4__ {TYPE_1__ mac; } ;
struct igc_adapter {TYPE_2__ hw; struct igc_mac_addr* mac_table; } ;

/* Variables and functions */
 int IGC_MAC_STATE_DEFAULT ; 
 int IGC_MAC_STATE_IN_USE ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  igc_rar_set_index (struct igc_adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void igc_set_default_mac_filter(struct igc_adapter *adapter)
{
	struct igc_mac_addr *mac_table = &adapter->mac_table[0];

	ether_addr_copy(mac_table->addr, adapter->hw.mac.addr);
	mac_table->state = IGC_MAC_STATE_DEFAULT | IGC_MAC_STATE_IN_USE;

	igc_rar_set_index(adapter, 0);
}