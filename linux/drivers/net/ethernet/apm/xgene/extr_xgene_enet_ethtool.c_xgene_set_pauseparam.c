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
struct xgene_enet_pdata {scalar_t__ phy_mode; int /*<<< orphan*/  rx_pause; TYPE_1__* mac_ops; int /*<<< orphan*/  tx_pause; scalar_t__ pause_autoneg; } ;
struct phy_device {int dummy; } ;
struct net_device {struct phy_device* phydev; } ;
struct ethtool_pauseparam {int /*<<< orphan*/  rx_pause; int /*<<< orphan*/  tx_pause; scalar_t__ autoneg; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* flowctl_rx ) (struct xgene_enet_pdata*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* flowctl_tx ) (struct xgene_enet_pdata*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PHY_INTERFACE_MODE_SGMII ; 
 struct xgene_enet_pdata* netdev_priv (struct net_device*) ; 
 scalar_t__ phy_interface_mode_is_rgmii (scalar_t__) ; 
 int /*<<< orphan*/  phy_set_asym_pause (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_validate_pause (struct phy_device*,struct ethtool_pauseparam*) ; 
 int /*<<< orphan*/  stub1 (struct xgene_enet_pdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct xgene_enet_pdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct xgene_enet_pdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct xgene_enet_pdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xgene_set_pauseparam(struct net_device *ndev,
				struct ethtool_pauseparam *pp)
{
	struct xgene_enet_pdata *pdata = netdev_priv(ndev);
	struct phy_device *phydev = ndev->phydev;

	if (phy_interface_mode_is_rgmii(pdata->phy_mode) ||
	    pdata->phy_mode == PHY_INTERFACE_MODE_SGMII) {
		if (!phydev)
			return -EINVAL;

		if (!phy_validate_pause(phydev, pp))
			return -EINVAL;

		pdata->pause_autoneg = pp->autoneg;
		pdata->tx_pause = pp->tx_pause;
		pdata->rx_pause = pp->rx_pause;

		phy_set_asym_pause(phydev, pp->rx_pause,  pp->tx_pause);

		if (!pp->autoneg) {
			pdata->mac_ops->flowctl_tx(pdata, pdata->tx_pause);
			pdata->mac_ops->flowctl_rx(pdata, pdata->rx_pause);
		}
	} else {
		if (pp->autoneg)
			return -EINVAL;

		pdata->tx_pause = pp->tx_pause;
		pdata->rx_pause = pp->rx_pause;

		pdata->mac_ops->flowctl_tx(pdata, pdata->tx_pause);
		pdata->mac_ops->flowctl_rx(pdata, pdata->rx_pause);
	}

	return 0;
}