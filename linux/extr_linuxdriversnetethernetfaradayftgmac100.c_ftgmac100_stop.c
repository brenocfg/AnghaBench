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
struct net_device {int /*<<< orphan*/  irq; scalar_t__ phydev; } ;
struct ftgmac100 {int /*<<< orphan*/  ndev; scalar_t__ use_ncsi; int /*<<< orphan*/  napi; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ FTGMAC100_OFFSET_IER ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  ftgmac100_free_buffers (struct ftgmac100*) ; 
 int /*<<< orphan*/  ftgmac100_free_rings (struct ftgmac100*) ; 
 int /*<<< orphan*/  ftgmac100_stop_hw (struct ftgmac100*) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ncsi_stop_dev (int /*<<< orphan*/ ) ; 
 struct ftgmac100* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  phy_stop (scalar_t__) ; 

__attribute__((used)) static int ftgmac100_stop(struct net_device *netdev)
{
	struct ftgmac100 *priv = netdev_priv(netdev);

	/* Note about the reset task: We are called with the rtnl lock
	 * held, so we are synchronized against the core of the reset
	 * task. We must not try to synchronously cancel it otherwise
	 * we can deadlock. But since it will test for netif_running()
	 * which has already been cleared by the net core, we don't
	 * anything special to do.
	 */

	/* disable all interrupts */
	iowrite32(0, priv->base + FTGMAC100_OFFSET_IER);

	netif_stop_queue(netdev);
	napi_disable(&priv->napi);
	netif_napi_del(&priv->napi);
	if (netdev->phydev)
		phy_stop(netdev->phydev);
	else if (priv->use_ncsi)
		ncsi_stop_dev(priv->ndev);

	ftgmac100_stop_hw(priv);
	free_irq(netdev->irq, netdev);
	ftgmac100_free_buffers(priv);
	ftgmac100_free_rings(priv);

	return 0;
}