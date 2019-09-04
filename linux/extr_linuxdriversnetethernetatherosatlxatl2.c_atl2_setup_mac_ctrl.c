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
struct atl2_hw {int retry_buf; scalar_t__ preamble_len; } ;
struct atl2_adapter {scalar_t__ link_duplex; struct atl2_hw hw; struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATL2_WRITE_REG (struct atl2_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ FULL_DUPLEX ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int MAC_CTRL_ADD_CRC ; 
 int MAC_CTRL_BC_EN ; 
 int MAC_CTRL_DUPLX ; 
 int MAC_CTRL_HALF_LEFT_BUF_MASK ; 
 int MAC_CTRL_HALF_LEFT_BUF_SHIFT ; 
 int MAC_CTRL_MACLP_CLK_PHY ; 
 int MAC_CTRL_MC_ALL_EN ; 
 int MAC_CTRL_PAD ; 
 int MAC_CTRL_PRMLEN_MASK ; 
 int MAC_CTRL_PRMLEN_SHIFT ; 
 int MAC_CTRL_PROMIS_EN ; 
 int MAC_CTRL_RX_EN ; 
 int MAC_CTRL_RX_FLOW ; 
 int MAC_CTRL_TX_EN ; 
 int MAC_CTRL_TX_FLOW ; 
 int /*<<< orphan*/  REG_MAC_CTRL ; 
 int /*<<< orphan*/  __atl2_vlan_mode (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void atl2_setup_mac_ctrl(struct atl2_adapter *adapter)
{
	u32 value;
	struct atl2_hw *hw = &adapter->hw;
	struct net_device *netdev = adapter->netdev;

	/* Config MAC CTRL Register */
	value = MAC_CTRL_TX_EN | MAC_CTRL_RX_EN | MAC_CTRL_MACLP_CLK_PHY;

	/* duplex */
	if (FULL_DUPLEX == adapter->link_duplex)
		value |= MAC_CTRL_DUPLX;

	/* flow control */
	value |= (MAC_CTRL_TX_FLOW | MAC_CTRL_RX_FLOW);

	/* PAD & CRC */
	value |= (MAC_CTRL_ADD_CRC | MAC_CTRL_PAD);

	/* preamble length */
	value |= (((u32)adapter->hw.preamble_len & MAC_CTRL_PRMLEN_MASK) <<
		MAC_CTRL_PRMLEN_SHIFT);

	/* vlan */
	__atl2_vlan_mode(netdev->features, &value);

	/* filter mode */
	value |= MAC_CTRL_BC_EN;
	if (netdev->flags & IFF_PROMISC)
		value |= MAC_CTRL_PROMIS_EN;
	else if (netdev->flags & IFF_ALLMULTI)
		value |= MAC_CTRL_MC_ALL_EN;

	/* half retry buffer */
	value |= (((u32)(adapter->hw.retry_buf &
		MAC_CTRL_HALF_LEFT_BUF_MASK)) << MAC_CTRL_HALF_LEFT_BUF_SHIFT);

	ATL2_WRITE_REG(hw, REG_MAC_CTRL, value);
}