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
typedef  int u32 ;
struct xgene_enet_pdata {scalar_t__ phy_mode; scalar_t__ tx_pause; scalar_t__ rx_pause; TYPE_1__* mac_ops; scalar_t__ pause_autoneg; } ;
struct phy_device {int supported; int advertising; scalar_t__ autoneg; } ;
struct net_device {struct phy_device* phydev; } ;
struct ethtool_pauseparam {scalar_t__ rx_pause; scalar_t__ tx_pause; scalar_t__ autoneg; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* flowctl_rx ) (struct xgene_enet_pdata*,scalar_t__) ;int /*<<< orphan*/  (* flowctl_tx ) (struct xgene_enet_pdata*,scalar_t__) ;} ;

/* Variables and functions */
 int ADVERTISED_Asym_Pause ; 
 int ADVERTISED_Pause ; 
 int EINVAL ; 
 scalar_t__ PHY_INTERFACE_MODE_SGMII ; 
 int SUPPORTED_Asym_Pause ; 
 int SUPPORTED_Pause ; 
 struct xgene_enet_pdata* netdev_priv (struct net_device*) ; 
 scalar_t__ phy_interface_mode_is_rgmii (scalar_t__) ; 
 int phy_start_aneg (struct phy_device*) ; 
 int /*<<< orphan*/  stub1 (struct xgene_enet_pdata*,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (struct xgene_enet_pdata*,scalar_t__) ; 
 int /*<<< orphan*/  stub3 (struct xgene_enet_pdata*,scalar_t__) ; 
 int /*<<< orphan*/  stub4 (struct xgene_enet_pdata*,scalar_t__) ; 

__attribute__((used)) static int xgene_set_pauseparam(struct net_device *ndev,
				struct ethtool_pauseparam *pp)
{
	struct xgene_enet_pdata *pdata = netdev_priv(ndev);
	struct phy_device *phydev = ndev->phydev;
	u32 oldadv, newadv;

	if (phy_interface_mode_is_rgmii(pdata->phy_mode) ||
	    pdata->phy_mode == PHY_INTERFACE_MODE_SGMII) {
		if (!phydev)
			return -EINVAL;

		if (!(phydev->supported & SUPPORTED_Pause) ||
		    (!(phydev->supported & SUPPORTED_Asym_Pause) &&
		     pp->rx_pause != pp->tx_pause))
			return -EINVAL;

		pdata->pause_autoneg = pp->autoneg;
		pdata->tx_pause = pp->tx_pause;
		pdata->rx_pause = pp->rx_pause;

		oldadv = phydev->advertising;
		newadv = oldadv & ~(ADVERTISED_Pause | ADVERTISED_Asym_Pause);

		if (pp->rx_pause)
			newadv |= ADVERTISED_Pause | ADVERTISED_Asym_Pause;

		if (pp->tx_pause)
			newadv ^= ADVERTISED_Asym_Pause;

		if (oldadv ^ newadv) {
			phydev->advertising = newadv;

			if (phydev->autoneg)
				return phy_start_aneg(phydev);

			if (!pp->autoneg) {
				pdata->mac_ops->flowctl_tx(pdata,
							   pdata->tx_pause);
				pdata->mac_ops->flowctl_rx(pdata,
							   pdata->rx_pause);
			}
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