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
struct net_device {int flags; int /*<<< orphan*/  features; } ;
struct atl1_hw {scalar_t__ hw_addr; scalar_t__ preamble_len; } ;
struct atl1_adapter {scalar_t__ link_duplex; scalar_t__ link_speed; struct atl1_hw hw; struct net_device* netdev; } ;

/* Variables and functions */
 scalar_t__ FULL_DUPLEX ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int MAC_CTRL_ADD_CRC ; 
 int MAC_CTRL_BC_EN ; 
 int MAC_CTRL_DUPLX ; 
 int MAC_CTRL_MC_ALL_EN ; 
 int MAC_CTRL_PAD ; 
 int MAC_CTRL_PRMLEN_MASK ; 
 int MAC_CTRL_PRMLEN_SHIFT ; 
 int MAC_CTRL_PROMIS_EN ; 
 int MAC_CTRL_RX_EN ; 
 int MAC_CTRL_RX_FLOW ; 
 scalar_t__ MAC_CTRL_SPEED_1000 ; 
 scalar_t__ MAC_CTRL_SPEED_10_100 ; 
 int MAC_CTRL_SPEED_SHIFT ; 
 int MAC_CTRL_TX_EN ; 
 int MAC_CTRL_TX_FLOW ; 
 scalar_t__ REG_MAC_CTRL ; 
 scalar_t__ SPEED_1000 ; 
 int /*<<< orphan*/  __atlx_vlan_mode (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 

__attribute__((used)) static void atl1_setup_mac_ctrl(struct atl1_adapter *adapter)
{
	u32 value;
	struct atl1_hw *hw = &adapter->hw;
	struct net_device *netdev = adapter->netdev;
	/* Config MAC CTRL Register */
	value = MAC_CTRL_TX_EN | MAC_CTRL_RX_EN;
	/* duplex */
	if (FULL_DUPLEX == adapter->link_duplex)
		value |= MAC_CTRL_DUPLX;
	/* speed */
	value |= ((u32) ((SPEED_1000 == adapter->link_speed) ?
			 MAC_CTRL_SPEED_1000 : MAC_CTRL_SPEED_10_100) <<
		  MAC_CTRL_SPEED_SHIFT);
	/* flow control */
	value |= (MAC_CTRL_TX_FLOW | MAC_CTRL_RX_FLOW);
	/* PAD & CRC */
	value |= (MAC_CTRL_ADD_CRC | MAC_CTRL_PAD);
	/* preamble length */
	value |= (((u32) adapter->hw.preamble_len
		   & MAC_CTRL_PRMLEN_MASK) << MAC_CTRL_PRMLEN_SHIFT);
	/* vlan */
	__atlx_vlan_mode(netdev->features, &value);
	/* rx checksum
	   if (adapter->rx_csum)
	   value |= MAC_CTRL_RX_CHKSUM_EN;
	 */
	/* filter mode */
	value |= MAC_CTRL_BC_EN;
	if (netdev->flags & IFF_PROMISC)
		value |= MAC_CTRL_PROMIS_EN;
	else if (netdev->flags & IFF_ALLMULTI)
		value |= MAC_CTRL_MC_ALL_EN;
	/* value |= MAC_CTRL_LOOPBACK; */
	iowrite32(value, hw->hw_addr + REG_MAC_CTRL);
}