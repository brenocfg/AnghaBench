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
struct e1000_hw {int dummy; } ;
struct e1000_adapter {int /*<<< orphan*/  active_vlans; int /*<<< orphan*/  flags; struct e1000_hw hw; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int E1000_READ_REG_ARRAY (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VFTA ; 
 int /*<<< orphan*/  __E1000_DOWN ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e1000_irq_disable (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_irq_enable (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_vlan_filter_on_off (struct e1000_adapter*,int) ; 
 int /*<<< orphan*/  e1000_vlan_used (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_write_vfta (struct e1000_hw*,int,int) ; 
 struct e1000_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int e1000_vlan_rx_kill_vid(struct net_device *netdev,
				  __be16 proto, u16 vid)
{
	struct e1000_adapter *adapter = netdev_priv(netdev);
	struct e1000_hw *hw = &adapter->hw;
	u32 vfta, index;

	if (!test_bit(__E1000_DOWN, &adapter->flags))
		e1000_irq_disable(adapter);
	if (!test_bit(__E1000_DOWN, &adapter->flags))
		e1000_irq_enable(adapter);

	/* remove VID from filter table */
	index = (vid >> 5) & 0x7F;
	vfta = E1000_READ_REG_ARRAY(hw, VFTA, index);
	vfta &= ~(1 << (vid & 0x1F));
	e1000_write_vfta(hw, index, vfta);

	clear_bit(vid, adapter->active_vlans);

	if (!e1000_vlan_used(adapter))
		e1000_vlan_filter_on_off(adapter, false);

	return 0;
}