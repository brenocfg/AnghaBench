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
struct net_device {int features; int flags; } ;
struct atl1e_hw {scalar_t__ preamble_len; } ;
struct atl1e_adapter {scalar_t__ link_duplex; scalar_t__ link_speed; struct atl1e_hw hw; struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_WRITE_REG (struct atl1e_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ FULL_DUPLEX ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int MAC_CTRL_ADD_CRC ; 
 int MAC_CTRL_BC_EN ; 
 int MAC_CTRL_DBG ; 
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
 int NETIF_F_RXALL ; 
 int /*<<< orphan*/  REG_MAC_CTRL ; 
 scalar_t__ SPEED_1000 ; 
 int /*<<< orphan*/  __atl1e_vlan_mode (int,int*) ; 

__attribute__((used)) static void atl1e_setup_mac_ctrl(struct atl1e_adapter *adapter)
{
	u32 value;
	struct atl1e_hw *hw = &adapter->hw;
	struct net_device *netdev = adapter->netdev;

	/* Config MAC CTRL Register */
	value = MAC_CTRL_TX_EN |
		MAC_CTRL_RX_EN ;

	if (FULL_DUPLEX == adapter->link_duplex)
		value |= MAC_CTRL_DUPLX;

	value |= ((u32)((SPEED_1000 == adapter->link_speed) ?
			  MAC_CTRL_SPEED_1000 : MAC_CTRL_SPEED_10_100) <<
			  MAC_CTRL_SPEED_SHIFT);
	value |= (MAC_CTRL_TX_FLOW | MAC_CTRL_RX_FLOW);

	value |= (MAC_CTRL_ADD_CRC | MAC_CTRL_PAD);
	value |= (((u32)adapter->hw.preamble_len &
		  MAC_CTRL_PRMLEN_MASK) << MAC_CTRL_PRMLEN_SHIFT);

	__atl1e_vlan_mode(netdev->features, &value);

	value |= MAC_CTRL_BC_EN;
	if (netdev->flags & IFF_PROMISC)
		value |= MAC_CTRL_PROMIS_EN;
	if (netdev->flags & IFF_ALLMULTI)
		value |= MAC_CTRL_MC_ALL_EN;
	if (netdev->features & NETIF_F_RXALL)
		value |= MAC_CTRL_DBG;
	AT_WRITE_REG(hw, REG_MAC_CTRL, value);
}