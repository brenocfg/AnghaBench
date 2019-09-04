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
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int dummy; } ;
struct ipoib_path {int /*<<< orphan*/  query; } ;
struct ipoib_neigh {int dummy; } ;
struct ipoib_dev_priv {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 struct ipoib_path* __path_find (struct net_device*,int /*<<< orphan*/ *) ; 
 struct ipoib_dev_priv* ipoib_priv (struct net_device*) ; 
 int /*<<< orphan*/  path_rec_start (struct net_device*,struct ipoib_path*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void neigh_refresh_path(struct ipoib_neigh *neigh, u8 *daddr,
			       struct net_device *dev)
{
	struct ipoib_dev_priv *priv = ipoib_priv(dev);
	struct ipoib_path *path;
	unsigned long flags;

	spin_lock_irqsave(&priv->lock, flags);

	path = __path_find(dev, daddr + 4);
	if (!path)
		goto out;
	if (!path->query)
		path_rec_start(dev, path);
out:
	spin_unlock_irqrestore(&priv->lock, flags);
}