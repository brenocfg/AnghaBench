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
struct phy_device {int supported; int advertising; scalar_t__ autoneg; } ;
struct net_device {struct phy_device* phydev; } ;
struct mac_device {int autoneg_pause; int rx_pause_req; int tx_pause_req; } ;
struct ethtool_pauseparam {int rx_pause; int tx_pause; int /*<<< orphan*/  autoneg; } ;
struct dpaa_priv {struct mac_device* mac_dev; } ;

/* Variables and functions */
 int ADVERTISED_Asym_Pause ; 
 int ADVERTISED_Pause ; 
 int EINVAL ; 
 int ENODEV ; 
 int SUPPORTED_Asym_Pause ; 
 int SUPPORTED_Pause ; 
 int /*<<< orphan*/  fman_get_pause_cfg (struct mac_device*,int*,int*) ; 
 int fman_set_mac_active_pause (struct mac_device*,int,int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,...) ; 
 struct dpaa_priv* netdev_priv (struct net_device*) ; 
 int phy_start_aneg (struct phy_device*) ; 

__attribute__((used)) static int dpaa_set_pauseparam(struct net_device *net_dev,
			       struct ethtool_pauseparam *epause)
{
	struct mac_device *mac_dev;
	struct phy_device *phydev;
	bool rx_pause, tx_pause;
	struct dpaa_priv *priv;
	u32 newadv, oldadv;
	int err;

	priv = netdev_priv(net_dev);
	mac_dev = priv->mac_dev;

	phydev = net_dev->phydev;
	if (!phydev) {
		netdev_err(net_dev, "phy device not initialized\n");
		return -ENODEV;
	}

	if (!(phydev->supported & SUPPORTED_Pause) ||
	    (!(phydev->supported & SUPPORTED_Asym_Pause) &&
	    (epause->rx_pause != epause->tx_pause)))
		return -EINVAL;

	/* The MAC should know how to handle PAUSE frame autonegotiation before
	 * adjust_link is triggered by a forced renegotiation of sym/asym PAUSE
	 * settings.
	 */
	mac_dev->autoneg_pause = !!epause->autoneg;
	mac_dev->rx_pause_req = !!epause->rx_pause;
	mac_dev->tx_pause_req = !!epause->tx_pause;

	/* Determine the sym/asym advertised PAUSE capabilities from the desired
	 * rx/tx pause settings.
	 */
	newadv = 0;
	if (epause->rx_pause)
		newadv = ADVERTISED_Pause | ADVERTISED_Asym_Pause;
	if (epause->tx_pause)
		newadv ^= ADVERTISED_Asym_Pause;

	oldadv = phydev->advertising &
			(ADVERTISED_Pause | ADVERTISED_Asym_Pause);

	/* If there are differences between the old and the new advertised
	 * values, restart PHY autonegotiation and advertise the new values.
	 */
	if (oldadv != newadv) {
		phydev->advertising &= ~(ADVERTISED_Pause
				| ADVERTISED_Asym_Pause);
		phydev->advertising |= newadv;
		if (phydev->autoneg) {
			err = phy_start_aneg(phydev);
			if (err < 0)
				netdev_err(net_dev, "phy_start_aneg() = %d\n",
					   err);
		}
	}

	fman_get_pause_cfg(mac_dev, &rx_pause, &tx_pause);
	err = fman_set_mac_active_pause(mac_dev, rx_pause, tx_pause);
	if (err < 0)
		netdev_err(net_dev, "set_mac_active_pause() = %d\n", err);

	return err;
}