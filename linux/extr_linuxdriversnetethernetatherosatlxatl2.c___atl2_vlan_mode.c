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
typedef  int /*<<< orphan*/  u32 ;
typedef  int netdev_features_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_CTRL_RMV_VLAN ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 

__attribute__((used)) static void __atl2_vlan_mode(netdev_features_t features, u32 *ctrl)
{
	if (features & NETIF_F_HW_VLAN_CTAG_RX) {
		/* enable VLAN tag insert/strip */
		*ctrl |= MAC_CTRL_RMV_VLAN;
	} else {
		/* disable VLAN tag insert/strip */
		*ctrl &= ~MAC_CTRL_RMV_VLAN;
	}
}