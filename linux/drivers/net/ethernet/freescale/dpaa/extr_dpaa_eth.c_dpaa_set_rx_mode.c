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
struct net_device {int flags; } ;
struct dpaa_priv {TYPE_1__* mac_dev; } ;
struct TYPE_2__ {int promisc; int (* set_promisc ) (int /*<<< orphan*/ ,int) ;int allmulti; int (* set_allmulti ) (int /*<<< orphan*/ ,int) ;int (* set_multi ) (struct net_device*,TYPE_1__*) ;int /*<<< orphan*/  fman_mac; } ;

/* Variables and functions */
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  drv ; 
 struct dpaa_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_err (struct dpaa_priv const*,int /*<<< orphan*/ ,struct net_device*,char*,int) ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 
 int stub2 (int /*<<< orphan*/ ,int) ; 
 int stub3 (struct net_device*,TYPE_1__*) ; 

__attribute__((used)) static void dpaa_set_rx_mode(struct net_device *net_dev)
{
	const struct dpaa_priv	*priv;
	int err;

	priv = netdev_priv(net_dev);

	if (!!(net_dev->flags & IFF_PROMISC) != priv->mac_dev->promisc) {
		priv->mac_dev->promisc = !priv->mac_dev->promisc;
		err = priv->mac_dev->set_promisc(priv->mac_dev->fman_mac,
						 priv->mac_dev->promisc);
		if (err < 0)
			netif_err(priv, drv, net_dev,
				  "mac_dev->set_promisc() = %d\n",
				  err);
	}

	if (!!(net_dev->flags & IFF_ALLMULTI) != priv->mac_dev->allmulti) {
		priv->mac_dev->allmulti = !priv->mac_dev->allmulti;
		err = priv->mac_dev->set_allmulti(priv->mac_dev->fman_mac,
						  priv->mac_dev->allmulti);
		if (err < 0)
			netif_err(priv, drv, net_dev,
				  "mac_dev->set_allmulti() = %d\n",
				  err);
	}

	err = priv->mac_dev->set_multi(net_dev, priv->mac_dev);
	if (err < 0)
		netif_err(priv, drv, net_dev, "mac_dev->set_multi() = %d\n",
			  err);
}