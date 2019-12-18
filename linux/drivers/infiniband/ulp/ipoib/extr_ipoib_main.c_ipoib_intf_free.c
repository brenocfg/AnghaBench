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
struct rdma_netdev {int /*<<< orphan*/ * clnt_priv; } ;
struct net_device {int /*<<< orphan*/  (* priv_destructor ) (struct net_device*) ;} ;
struct ipoib_dev_priv {int /*<<< orphan*/  (* next_priv_destructor ) (struct net_device*) ;} ;

/* Variables and functions */
 struct ipoib_dev_priv* ipoib_priv (struct net_device*) ; 
 int /*<<< orphan*/  kfree (struct ipoib_dev_priv*) ; 
 struct rdma_netdev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct net_device*) ; 

void ipoib_intf_free(struct net_device *dev)
{
	struct ipoib_dev_priv *priv = ipoib_priv(dev);
	struct rdma_netdev *rn = netdev_priv(dev);

	dev->priv_destructor = priv->next_priv_destructor;
	if (dev->priv_destructor)
		dev->priv_destructor(dev);

	/*
	 * There are some error flows around register_netdev failing that may
	 * attempt to call priv_destructor twice, prevent that from happening.
	 */
	dev->priv_destructor = NULL;

	/* unregister/destroy is very complicated. Make bugs more obvious. */
	rn->clnt_priv = NULL;

	kfree(priv);
}