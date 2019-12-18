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
struct net_device {scalar_t__ phydev; } ;
struct dnet {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  dnet_reset_hw (struct dnet*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct dnet* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  phy_stop (scalar_t__) ; 

__attribute__((used)) static int dnet_close(struct net_device *dev)
{
	struct dnet *bp = netdev_priv(dev);

	netif_stop_queue(dev);
	napi_disable(&bp->napi);

	if (dev->phydev)
		phy_stop(dev->phydev);

	dnet_reset_hw(bp);
	netif_carrier_off(dev);

	return 0;
}