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
struct pcmcia_device {int config_index; int /*<<< orphan*/  config_flags; TYPE_1__** resource; struct net_device* priv; int /*<<< orphan*/  dev; } ;
struct net_device {int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/  watchdog_timeo; int /*<<< orphan*/ * netdev_ops; } ;
struct el3_private {int /*<<< orphan*/  lock; struct pcmcia_device* p_dev; } ;
struct TYPE_2__ {int end; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONF_ENABLE_IRQ ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IO_DATA_PATH_WIDTH_16 ; 
 int /*<<< orphan*/  TX_TIMEOUT ; 
 struct net_device* alloc_etherdev (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  el3_netdev_ops ; 
 int /*<<< orphan*/  netdev_ethtool_ops ; 
 struct el3_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int tc589_config (struct pcmcia_device*) ; 

__attribute__((used)) static int tc589_probe(struct pcmcia_device *link)
{
	struct el3_private *lp;
	struct net_device *dev;

	dev_dbg(&link->dev, "3c589_attach()\n");

	/* Create new ethernet device */
	dev = alloc_etherdev(sizeof(struct el3_private));
	if (!dev)
		return -ENOMEM;
	lp = netdev_priv(dev);
	link->priv = dev;
	lp->p_dev = link;

	spin_lock_init(&lp->lock);
	link->resource[0]->end = 16;
	link->resource[0]->flags |= IO_DATA_PATH_WIDTH_16;

	link->config_flags |= CONF_ENABLE_IRQ;
	link->config_index = 1;

	dev->netdev_ops = &el3_netdev_ops;
	dev->watchdog_timeo = TX_TIMEOUT;

	dev->ethtool_ops = &netdev_ethtool_ops;

	return tc589_config(link);
}