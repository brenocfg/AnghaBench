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
struct phy_device {scalar_t__ duplex; scalar_t__ speed; scalar_t__ link; } ;
struct net_device {struct phy_device* phydev; } ;
struct fec_enet_private {scalar_t__ full_duplex; scalar_t__ speed; scalar_t__ link; int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  fec_restart (struct net_device*) ; 
 int /*<<< orphan*/  fec_stop (struct net_device*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct fec_enet_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_present (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_lock_bh (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_unlock_bh (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_wake_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  phy_print_status (struct phy_device*) ; 

__attribute__((used)) static void fec_enet_adjust_link(struct net_device *ndev)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	struct phy_device *phy_dev = ndev->phydev;
	int status_change = 0;

	/*
	 * If the netdev is down, or is going down, we're not interested
	 * in link state events, so just mark our idea of the link as down
	 * and ignore the event.
	 */
	if (!netif_running(ndev) || !netif_device_present(ndev)) {
		fep->link = 0;
	} else if (phy_dev->link) {
		if (!fep->link) {
			fep->link = phy_dev->link;
			status_change = 1;
		}

		if (fep->full_duplex != phy_dev->duplex) {
			fep->full_duplex = phy_dev->duplex;
			status_change = 1;
		}

		if (phy_dev->speed != fep->speed) {
			fep->speed = phy_dev->speed;
			status_change = 1;
		}

		/* if any of the above changed restart the FEC */
		if (status_change) {
			napi_disable(&fep->napi);
			netif_tx_lock_bh(ndev);
			fec_restart(ndev);
			netif_tx_wake_all_queues(ndev);
			netif_tx_unlock_bh(ndev);
			napi_enable(&fep->napi);
		}
	} else {
		if (fep->link) {
			napi_disable(&fep->napi);
			netif_tx_lock_bh(ndev);
			fec_stop(ndev);
			netif_tx_unlock_bh(ndev);
			napi_enable(&fep->napi);
			fep->link = phy_dev->link;
			status_change = 1;
		}
	}

	if (status_change)
		phy_print_status(phy_dev);
}