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
struct qmimux_priv {int /*<<< orphan*/  stats64; struct net_device* real_dev; } ;
struct net_device {int dummy; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 struct qmimux_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_upper_dev_unlink (struct net_device*,struct net_device*) ; 
 int /*<<< orphan*/  unregister_netdevice_queue (struct net_device*,struct list_head*) ; 

__attribute__((used)) static void qmimux_unregister_device(struct net_device *dev,
				     struct list_head *head)
{
	struct qmimux_priv *priv = netdev_priv(dev);
	struct net_device *real_dev = priv->real_dev;

	free_percpu(priv->stats64);
	netdev_upper_dev_unlink(real_dev, dev);
	unregister_netdevice_queue(dev, head);

	/* Get rid of the reference to real_dev */
	dev_put(real_dev);
}