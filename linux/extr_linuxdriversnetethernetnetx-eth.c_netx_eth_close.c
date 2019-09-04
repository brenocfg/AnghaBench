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
struct netx_eth_priv {scalar_t__ xpec_base; } ;
struct net_device {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 scalar_t__ ETH_MAC_LOCAL_CONFIG ; 
 scalar_t__ NETX_XPEC_RAM_START_OFS ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 struct netx_eth_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int netx_eth_close(struct net_device *ndev)
{
	struct netx_eth_priv *priv = netdev_priv(ndev);

	netif_stop_queue(ndev);

	writel(0,
	    priv->xpec_base + NETX_XPEC_RAM_START_OFS + ETH_MAC_LOCAL_CONFIG);

	free_irq(ndev->irq, ndev);

	return 0;
}