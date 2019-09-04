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
struct net_device {int /*<<< orphan*/  mem_end; int /*<<< orphan*/  mem_start; int /*<<< orphan*/  base_addr; int /*<<< orphan*/  dev; int /*<<< orphan*/  phydev; int /*<<< orphan*/  name; int /*<<< orphan*/  irq; } ;
struct ethoc {int old_link; int old_duplex; int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ethoc_init_ring (struct ethoc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ethoc_interrupt ; 
 int /*<<< orphan*/  ethoc_reset (struct ethoc*) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct ethoc* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_msg_ifup (struct ethoc*) ; 
 scalar_t__ netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  phy_start (int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 

__attribute__((used)) static int ethoc_open(struct net_device *dev)
{
	struct ethoc *priv = netdev_priv(dev);
	int ret;

	ret = request_irq(dev->irq, ethoc_interrupt, IRQF_SHARED,
			dev->name, dev);
	if (ret)
		return ret;

	napi_enable(&priv->napi);

	ethoc_init_ring(priv, dev->mem_start);
	ethoc_reset(priv);

	if (netif_queue_stopped(dev)) {
		dev_dbg(&dev->dev, " resuming queue\n");
		netif_wake_queue(dev);
	} else {
		dev_dbg(&dev->dev, " starting queue\n");
		netif_start_queue(dev);
	}

	priv->old_link = -1;
	priv->old_duplex = -1;

	phy_start(dev->phydev);

	if (netif_msg_ifup(priv)) {
		dev_info(&dev->dev, "I/O: %08lx Memory: %08lx-%08lx\n",
				dev->base_addr, dev->mem_start, dev->mem_end);
	}

	return 0;
}