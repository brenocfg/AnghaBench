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
typedef  int u8 ;
struct net_device {int dummy; } ;
struct ethtool_pauseparam {scalar_t__ autoneg; scalar_t__ rx_pause; scalar_t__ tx_pause; } ;
struct alx_hw {int adv_cfg; int flowctrl; } ;
struct alx_priv {struct alx_hw hw; } ;

/* Variables and functions */
 int ADVERTISED_Autoneg ; 
 int ALX_FC_ANEG ; 
 int ALX_FC_RX ; 
 int ALX_FC_TX ; 
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  alx_cfg_mac_flowcontrol (struct alx_hw*,int) ; 
 int alx_setup_speed_duplex (struct alx_hw*,int,int) ; 
 struct alx_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int alx_set_pauseparam(struct net_device *netdev,
			      struct ethtool_pauseparam *pause)
{
	struct alx_priv *alx = netdev_priv(netdev);
	struct alx_hw *hw = &alx->hw;
	int err = 0;
	bool reconfig_phy = false;
	u8 fc = 0;

	if (pause->tx_pause)
		fc |= ALX_FC_TX;
	if (pause->rx_pause)
		fc |= ALX_FC_RX;
	if (pause->autoneg)
		fc |= ALX_FC_ANEG;

	ASSERT_RTNL();

	/* restart auto-neg for auto-mode */
	if (hw->adv_cfg & ADVERTISED_Autoneg) {
		if (!((fc ^ hw->flowctrl) & ALX_FC_ANEG))
			reconfig_phy = true;
		if (fc & hw->flowctrl & ALX_FC_ANEG &&
		    (fc ^ hw->flowctrl) & (ALX_FC_RX | ALX_FC_TX))
			reconfig_phy = true;
	}

	if (reconfig_phy) {
		err = alx_setup_speed_duplex(hw, hw->adv_cfg, fc);
		if (err)
			return err;
	}

	/* flow control on mac */
	if ((fc ^ hw->flowctrl) & (ALX_FC_RX | ALX_FC_TX))
		alx_cfg_mac_flowcontrol(hw, fc);

	hw->flowctrl = fc;

	return 0;
}