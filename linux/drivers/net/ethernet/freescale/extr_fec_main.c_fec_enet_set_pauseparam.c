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
struct net_device {int /*<<< orphan*/  phydev; } ;
struct fec_enet_private {int /*<<< orphan*/  napi; int /*<<< orphan*/  pause_flag; } ;
struct ethtool_pauseparam {scalar_t__ tx_pause; scalar_t__ rx_pause; scalar_t__ autoneg; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  FEC_PAUSE_FLAG_AUTONEG ; 
 int /*<<< orphan*/  FEC_PAUSE_FLAG_ENABLE ; 
 int /*<<< orphan*/  fec_restart (struct net_device*) ; 
 int /*<<< orphan*/  fec_stop (struct net_device*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 struct fec_enet_private* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_lock_bh (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_unlock_bh (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_wake_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  phy_set_sym_pause (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  phy_start_aneg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fec_enet_set_pauseparam(struct net_device *ndev,
				   struct ethtool_pauseparam *pause)
{
	struct fec_enet_private *fep = netdev_priv(ndev);

	if (!ndev->phydev)
		return -ENODEV;

	if (pause->tx_pause != pause->rx_pause) {
		netdev_info(ndev,
			"hardware only support enable/disable both tx and rx");
		return -EINVAL;
	}

	fep->pause_flag = 0;

	/* tx pause must be same as rx pause */
	fep->pause_flag |= pause->rx_pause ? FEC_PAUSE_FLAG_ENABLE : 0;
	fep->pause_flag |= pause->autoneg ? FEC_PAUSE_FLAG_AUTONEG : 0;

	phy_set_sym_pause(ndev->phydev, pause->rx_pause, pause->tx_pause,
			  pause->autoneg);

	if (pause->autoneg) {
		if (netif_running(ndev))
			fec_stop(ndev);
		phy_start_aneg(ndev->phydev);
	}
	if (netif_running(ndev)) {
		napi_disable(&fep->napi);
		netif_tx_lock_bh(ndev);
		fec_restart(ndev);
		netif_tx_wake_all_queues(ndev);
		netif_tx_unlock_bh(ndev);
		napi_enable(&fep->napi);
	}

	return 0;
}