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
typedef  int /*<<< orphan*/  u16 ;
struct sky2_port {int /*<<< orphan*/  port; struct sky2_hw* hw; } ;
struct sky2_hw {int dummy; } ;
struct net_device {int /*<<< orphan*/  vlan_features; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int NETIF_F_HW_VLAN_CTAG_TX ; 
 int /*<<< orphan*/  RX_GMF_CTRL_T ; 
 int /*<<< orphan*/  RX_VLAN_STRIP_OFF ; 
 int /*<<< orphan*/  RX_VLAN_STRIP_ON ; 
 int /*<<< orphan*/  SKY2_VLAN_OFFLOADS ; 
 int /*<<< orphan*/  SK_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TX_GMF_CTRL_T ; 
 int /*<<< orphan*/  TX_VLAN_TAG_OFF ; 
 int /*<<< orphan*/  TX_VLAN_TAG_ON ; 
 struct sky2_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  sky2_write32 (struct sky2_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sky2_vlan_mode(struct net_device *dev, netdev_features_t features)
{
	struct sky2_port *sky2 = netdev_priv(dev);
	struct sky2_hw *hw = sky2->hw;
	u16 port = sky2->port;

	if (features & NETIF_F_HW_VLAN_CTAG_RX)
		sky2_write32(hw, SK_REG(port, RX_GMF_CTRL_T),
			     RX_VLAN_STRIP_ON);
	else
		sky2_write32(hw, SK_REG(port, RX_GMF_CTRL_T),
			     RX_VLAN_STRIP_OFF);

	if (features & NETIF_F_HW_VLAN_CTAG_TX) {
		sky2_write32(hw, SK_REG(port, TX_GMF_CTRL_T),
			     TX_VLAN_TAG_ON);

		dev->vlan_features |= SKY2_VLAN_OFFLOADS;
	} else {
		sky2_write32(hw, SK_REG(port, TX_GMF_CTRL_T),
			     TX_VLAN_TAG_OFF);

		/* Can't do transmit offload of vlan without hw vlan */
		dev->vlan_features &= ~SKY2_VLAN_OFFLOADS;
	}
}