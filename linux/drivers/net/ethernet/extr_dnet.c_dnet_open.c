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
struct dnet {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  dnet_init_hw (struct dnet*) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct dnet* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  phy_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_start_aneg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dnet_open(struct net_device *dev)
{
	struct dnet *bp = netdev_priv(dev);

	/* if the phy is not yet register, retry later */
	if (!dev->phydev)
		return -EAGAIN;

	napi_enable(&bp->napi);
	dnet_init_hw(bp);

	phy_start_aneg(dev->phydev);

	/* schedule a link state check */
	phy_start(dev->phydev);

	netif_start_queue(dev);

	return 0;
}