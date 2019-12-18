#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct TYPE_5__ {int /*<<< orphan*/ * mac_addr; } ;
struct TYPE_4__ {scalar_t__ vlan_id; } ;
struct TYPE_6__ {TYPE_2__ mac; TYPE_1__ mac_vlan; } ;
struct ice_fltr_info {scalar_t__ flag; TYPE_3__ l_data; } ;

/* Variables and functions */
 scalar_t__ ICE_FLTR_TX ; 
 int /*<<< orphan*/  ICE_PROMISC_BCAST_RX ; 
 int /*<<< orphan*/  ICE_PROMISC_BCAST_TX ; 
 int /*<<< orphan*/  ICE_PROMISC_MCAST_RX ; 
 int /*<<< orphan*/  ICE_PROMISC_MCAST_TX ; 
 int /*<<< orphan*/  ICE_PROMISC_UCAST_RX ; 
 int /*<<< orphan*/  ICE_PROMISC_UCAST_TX ; 
 int /*<<< orphan*/  ICE_PROMISC_VLAN_RX ; 
 int /*<<< orphan*/  ICE_PROMISC_VLAN_TX ; 
 scalar_t__ is_broadcast_ether_addr (int /*<<< orphan*/ *) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ *) ; 
 scalar_t__ is_unicast_ether_addr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u8 ice_determine_promisc_mask(struct ice_fltr_info *fi)
{
	u16 vid = fi->l_data.mac_vlan.vlan_id;
	u8 *macaddr = fi->l_data.mac.mac_addr;
	bool is_tx_fltr = false;
	u8 promisc_mask = 0;

	if (fi->flag == ICE_FLTR_TX)
		is_tx_fltr = true;

	if (is_broadcast_ether_addr(macaddr))
		promisc_mask |= is_tx_fltr ?
			ICE_PROMISC_BCAST_TX : ICE_PROMISC_BCAST_RX;
	else if (is_multicast_ether_addr(macaddr))
		promisc_mask |= is_tx_fltr ?
			ICE_PROMISC_MCAST_TX : ICE_PROMISC_MCAST_RX;
	else if (is_unicast_ether_addr(macaddr))
		promisc_mask |= is_tx_fltr ?
			ICE_PROMISC_UCAST_TX : ICE_PROMISC_UCAST_RX;
	if (vid)
		promisc_mask |= is_tx_fltr ?
			ICE_PROMISC_VLAN_TX : ICE_PROMISC_VLAN_RX;

	return promisc_mask;
}