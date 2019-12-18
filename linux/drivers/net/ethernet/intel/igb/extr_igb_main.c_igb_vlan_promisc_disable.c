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
typedef  scalar_t__ u32 ;
struct igb_adapter {int flags; } ;

/* Variables and functions */
 scalar_t__ E1000_VLAN_FILTER_TBL_SIZE ; 
 int IGB_FLAG_VLAN_PROMISC ; 
 scalar_t__ VFTA_BLOCK_SIZE ; 
 int /*<<< orphan*/  igb_scrub_vfta (struct igb_adapter*,scalar_t__) ; 

__attribute__((used)) static void igb_vlan_promisc_disable(struct igb_adapter *adapter)
{
	u32 i;

	/* We are not in VLAN promisc, nothing to do */
	if (!(adapter->flags & IGB_FLAG_VLAN_PROMISC))
		return;

	/* Set flag so we don't redo unnecessary work */
	adapter->flags &= ~IGB_FLAG_VLAN_PROMISC;

	for (i = 0; i < E1000_VLAN_FILTER_TBL_SIZE; i += VFTA_BLOCK_SIZE)
		igb_scrub_vfta(adapter, i);
}