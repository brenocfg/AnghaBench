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
struct net_device {int dummy; } ;
struct ipoib_dev_priv {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ipoib_mcast_schedule_join_thread (struct ipoib_dev_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipoib_dbg_mcast (struct ipoib_dev_priv*,char*) ; 
 struct ipoib_dev_priv* ipoib_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void ipoib_mcast_start_thread(struct net_device *dev)
{
	struct ipoib_dev_priv *priv = ipoib_priv(dev);
	unsigned long flags;

	ipoib_dbg_mcast(priv, "starting multicast thread\n");

	spin_lock_irqsave(&priv->lock, flags);
	__ipoib_mcast_schedule_join_thread(priv, NULL, 0);
	spin_unlock_irqrestore(&priv->lock, flags);
}