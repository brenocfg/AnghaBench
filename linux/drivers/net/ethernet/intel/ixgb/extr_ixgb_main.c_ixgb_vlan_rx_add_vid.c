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
typedef  int u32 ;
typedef  int u16 ;
struct net_device {int dummy; } ;
struct ixgb_adapter {int /*<<< orphan*/  active_vlans; int /*<<< orphan*/  hw; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int IXGB_READ_REG_ARRAY (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VFTA ; 
 int /*<<< orphan*/  ixgb_write_vfta (int /*<<< orphan*/ *,int,int) ; 
 struct ixgb_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ixgb_vlan_rx_add_vid(struct net_device *netdev, __be16 proto, u16 vid)
{
	struct ixgb_adapter *adapter = netdev_priv(netdev);
	u32 vfta, index;

	/* add VID to filter table */

	index = (vid >> 5) & 0x7F;
	vfta = IXGB_READ_REG_ARRAY(&adapter->hw, VFTA, index);
	vfta |= (1 << (vid & 0x1F));
	ixgb_write_vfta(&adapter->hw, index, vfta);
	set_bit(vid, adapter->active_vlans);

	return 0;
}