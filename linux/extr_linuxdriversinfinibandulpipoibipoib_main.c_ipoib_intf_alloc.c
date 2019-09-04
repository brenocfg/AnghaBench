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
struct rdma_netdev {struct ipoib_dev_priv* clnt_priv; } ;
struct net_device {int /*<<< orphan*/ * priv_destructor; int /*<<< orphan*/ * netdev_ops; } ;
struct ipoib_dev_priv {int hca_caps; int /*<<< orphan*/ * next_priv_destructor; int /*<<< orphan*/ * rn_ops; int /*<<< orphan*/  port; struct ib_device* ca; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IB_DEVICE_VIRTUAL_FUNCTION ; 
 int /*<<< orphan*/  ipoib_build_priv (struct net_device*) ; 
 struct net_device* ipoib_get_netdev (struct ib_device*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  ipoib_netdev_ops_pf ; 
 int /*<<< orphan*/  ipoib_netdev_ops_vf ; 
 int /*<<< orphan*/  kfree (struct ipoib_dev_priv*) ; 
 struct ipoib_dev_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct rdma_netdev* netdev_priv (struct net_device*) ; 

struct ipoib_dev_priv *ipoib_intf_alloc(struct ib_device *hca, u8 port,
					const char *name)
{
	struct net_device *dev;
	struct ipoib_dev_priv *priv;
	struct rdma_netdev *rn;

	priv = kzalloc(sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return NULL;

	priv->ca = hca;
	priv->port = port;

	dev = ipoib_get_netdev(hca, port, name);
	if (!dev)
		goto free_priv;

	priv->rn_ops = dev->netdev_ops;

	/* fixme : should be after the query_cap */
	if (priv->hca_caps & IB_DEVICE_VIRTUAL_FUNCTION)
		dev->netdev_ops	= &ipoib_netdev_ops_vf;
	else
		dev->netdev_ops	= &ipoib_netdev_ops_pf;

	rn = netdev_priv(dev);
	rn->clnt_priv = priv;

	/*
	 * Only the child register_netdev flows can handle priv_destructor
	 * being set, so we force it to NULL here and handle manually until it
	 * is safe to turn on.
	 */
	priv->next_priv_destructor = dev->priv_destructor;
	dev->priv_destructor = NULL;

	ipoib_build_priv(dev);

	return priv;
free_priv:
	kfree(priv);
	return NULL;
}