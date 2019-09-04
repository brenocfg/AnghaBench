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
struct TYPE_2__ {int /*<<< orphan*/  tx_errors; } ;
struct net_device {TYPE_1__ stats; int /*<<< orphan*/  dev; } ;
struct mpc52xx_fec_priv {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mpc52xx_fec_reset (struct net_device*) ; 
 struct mpc52xx_fec_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void mpc52xx_fec_tx_timeout(struct net_device *dev)
{
	struct mpc52xx_fec_priv *priv = netdev_priv(dev);
	unsigned long flags;

	dev_warn(&dev->dev, "transmit timed out\n");

	spin_lock_irqsave(&priv->lock, flags);
	mpc52xx_fec_reset(dev);
	dev->stats.tx_errors++;
	spin_unlock_irqrestore(&priv->lock, flags);

	netif_wake_queue(dev);
}