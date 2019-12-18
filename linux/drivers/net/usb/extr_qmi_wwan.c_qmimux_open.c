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
struct qmimux_priv {struct net_device* real_dev; } ;
struct net_device {int flags; } ;

/* Variables and functions */
 int ENETDOWN ; 
 int IFF_UP ; 
 struct qmimux_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 

__attribute__((used)) static int qmimux_open(struct net_device *dev)
{
	struct qmimux_priv *priv = netdev_priv(dev);
	struct net_device *real_dev = priv->real_dev;

	if (!(priv->real_dev->flags & IFF_UP))
		return -ENETDOWN;

	if (netif_carrier_ok(real_dev))
		netif_carrier_on(dev);
	return 0;
}