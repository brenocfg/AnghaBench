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
typedef  int u32 ;
typedef  int u16 ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int status; } ;
struct e1000_hw {TYPE_1__ mng_cookie; } ;
struct e1000_adapter {int mng_vlan_id; int /*<<< orphan*/  active_vlans; struct e1000_hw hw; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int E1000_MNG_DHCP_COOKIE_STATUS_VLAN_SUPPORT ; 
 int E1000_READ_REG_ARRAY (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VFTA ; 
 int /*<<< orphan*/  e1000_vlan_filter_on_off (struct e1000_adapter*,int) ; 
 int /*<<< orphan*/  e1000_vlan_used (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_write_vfta (struct e1000_hw*,int,int) ; 
 struct e1000_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int e1000_vlan_rx_add_vid(struct net_device *netdev,
				 __be16 proto, u16 vid)
{
	struct e1000_adapter *adapter = netdev_priv(netdev);
	struct e1000_hw *hw = &adapter->hw;
	u32 vfta, index;

	if ((hw->mng_cookie.status &
	     E1000_MNG_DHCP_COOKIE_STATUS_VLAN_SUPPORT) &&
	    (vid == adapter->mng_vlan_id))
		return 0;

	if (!e1000_vlan_used(adapter))
		e1000_vlan_filter_on_off(adapter, true);

	/* add VID to filter table */
	index = (vid >> 5) & 0x7F;
	vfta = E1000_READ_REG_ARRAY(hw, VFTA, index);
	vfta |= (1 << (vid & 0x1F));
	e1000_write_vfta(hw, index, vfta);

	set_bit(vid, adapter->active_vlans);

	return 0;
}