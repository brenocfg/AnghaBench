#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pcmcia_device {int config_index; int /*<<< orphan*/  config_regs; int /*<<< orphan*/  config_flags; TYPE_1__** resource; struct net_device* priv; int /*<<< orphan*/  dev; } ;
struct net_device {int /*<<< orphan*/  watchdog_timeo; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  tx_free_frames; int /*<<< orphan*/  bank_lock; struct pcmcia_device* p_dev; } ;
typedef  TYPE_2__ mace_private ;
struct TYPE_4__ {int end; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AM2150_MAX_TX_FRAMES ; 
 int /*<<< orphan*/  CONF_ENABLE_IRQ ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IO_DATA_PATH_WIDTH_AUTO ; 
 int /*<<< orphan*/  PRESENT_OPTION ; 
 int /*<<< orphan*/  TX_TIMEOUT ; 
 struct net_device* alloc_etherdev (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mace_netdev_ops ; 
 int /*<<< orphan*/  netdev_ethtool_ops ; 
 TYPE_2__* netdev_priv (struct net_device*) ; 
 int nmclan_config (struct pcmcia_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nmclan_probe(struct pcmcia_device *link)
{
    mace_private *lp;
    struct net_device *dev;

    dev_dbg(&link->dev, "nmclan_attach()\n");

    /* Create new ethernet device */
    dev = alloc_etherdev(sizeof(mace_private));
    if (!dev)
	    return -ENOMEM;
    lp = netdev_priv(dev);
    lp->p_dev = link;
    link->priv = dev;
    
    spin_lock_init(&lp->bank_lock);
    link->resource[0]->end = 32;
    link->resource[0]->flags |= IO_DATA_PATH_WIDTH_AUTO;
    link->config_flags |= CONF_ENABLE_IRQ;
    link->config_index = 1;
    link->config_regs = PRESENT_OPTION;

    lp->tx_free_frames=AM2150_MAX_TX_FRAMES;

    dev->netdev_ops = &mace_netdev_ops;
    dev->ethtool_ops = &netdev_ethtool_ops;
    dev->watchdog_timeo = TX_TIMEOUT;

    return nmclan_config(link);
}