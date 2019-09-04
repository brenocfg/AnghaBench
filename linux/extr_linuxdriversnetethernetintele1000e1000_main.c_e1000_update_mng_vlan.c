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
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ vlan_id; int status; } ;
struct e1000_hw {TYPE_1__ mng_cookie; } ;
struct e1000_adapter {scalar_t__ mng_vlan_id; int /*<<< orphan*/  active_vlans; struct net_device* netdev; struct e1000_hw hw; } ;

/* Variables and functions */
 int E1000_MNG_DHCP_COOKIE_STATUS_VLAN_SUPPORT ; 
 scalar_t__ E1000_MNG_VLAN_NONE ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  e1000_vlan_rx_add_vid (struct net_device*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  e1000_vlan_rx_kill_vid (struct net_device*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  e1000_vlan_used (struct e1000_adapter*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void e1000_update_mng_vlan(struct e1000_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	struct net_device *netdev = adapter->netdev;
	u16 vid = hw->mng_cookie.vlan_id;
	u16 old_vid = adapter->mng_vlan_id;

	if (!e1000_vlan_used(adapter))
		return;

	if (!test_bit(vid, adapter->active_vlans)) {
		if (hw->mng_cookie.status &
		    E1000_MNG_DHCP_COOKIE_STATUS_VLAN_SUPPORT) {
			e1000_vlan_rx_add_vid(netdev, htons(ETH_P_8021Q), vid);
			adapter->mng_vlan_id = vid;
		} else {
			adapter->mng_vlan_id = E1000_MNG_VLAN_NONE;
		}
		if ((old_vid != (u16)E1000_MNG_VLAN_NONE) &&
		    (vid != old_vid) &&
		    !test_bit(old_vid, adapter->active_vlans))
			e1000_vlan_rx_kill_vid(netdev, htons(ETH_P_8021Q),
					       old_vid);
	} else {
		adapter->mng_vlan_id = vid;
	}
}