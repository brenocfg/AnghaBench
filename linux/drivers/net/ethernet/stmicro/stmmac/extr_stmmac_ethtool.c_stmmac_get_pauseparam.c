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
struct stmmac_priv {int /*<<< orphan*/  phylink; int /*<<< orphan*/  ioaddr; TYPE_1__* hw; } ;
struct rgmii_adv {int /*<<< orphan*/  pause; } ;
struct net_device {int dummy; } ;
struct ethtool_pauseparam {int autoneg; } ;
struct TYPE_2__ {scalar_t__ pcs; } ;

/* Variables and functions */
 struct stmmac_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phylink_ethtool_get_pauseparam (int /*<<< orphan*/ ,struct ethtool_pauseparam*) ; 
 int /*<<< orphan*/  stmmac_pcs_get_adv_lp (struct stmmac_priv*,int /*<<< orphan*/ ,struct rgmii_adv*) ; 

__attribute__((used)) static void
stmmac_get_pauseparam(struct net_device *netdev,
		      struct ethtool_pauseparam *pause)
{
	struct stmmac_priv *priv = netdev_priv(netdev);
	struct rgmii_adv adv_lp;

	if (priv->hw->pcs && !stmmac_pcs_get_adv_lp(priv, priv->ioaddr, &adv_lp)) {
		pause->autoneg = 1;
		if (!adv_lp.pause)
			return;
	} else {
		phylink_ethtool_get_pauseparam(priv->phylink, pause);
	}
}