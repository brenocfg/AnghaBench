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
struct net_device {int dummy; } ;
struct ethtool_pauseparam {int autoneg; int tx_pause; int rx_pause; } ;
struct alx_hw {int flowctrl; int adv_cfg; } ;
struct alx_priv {struct alx_hw hw; } ;

/* Variables and functions */
 int ADVERTISED_Autoneg ; 
 int ALX_FC_ANEG ; 
 int ALX_FC_RX ; 
 int ALX_FC_TX ; 
 struct alx_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void alx_get_pauseparam(struct net_device *netdev,
			       struct ethtool_pauseparam *pause)
{
	struct alx_priv *alx = netdev_priv(netdev);
	struct alx_hw *hw = &alx->hw;

	pause->autoneg = !!(hw->flowctrl & ALX_FC_ANEG &&
			    hw->adv_cfg & ADVERTISED_Autoneg);
	pause->tx_pause = !!(hw->flowctrl & ALX_FC_TX);
	pause->rx_pause = !!(hw->flowctrl & ALX_FC_RX);
}