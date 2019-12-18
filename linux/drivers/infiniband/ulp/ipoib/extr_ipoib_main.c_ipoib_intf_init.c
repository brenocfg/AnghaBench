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
typedef  int /*<<< orphan*/  u8 ;
struct rdma_netdev {struct ipoib_dev_priv* clnt_priv; struct ib_device* hca; int /*<<< orphan*/  detach_mcast; int /*<<< orphan*/  attach_mcast; int /*<<< orphan*/  send; } ;
struct net_device {int /*<<< orphan*/ * priv_destructor; int /*<<< orphan*/ * netdev_ops; } ;
struct ipoib_dev_priv {int /*<<< orphan*/ * next_priv_destructor; int /*<<< orphan*/ * rn_ops; int /*<<< orphan*/  port; struct ib_device* ca; } ;
struct TYPE_2__ {int device_cap_flags; } ;
struct ib_device {TYPE_1__ attrs; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IB_DEVICE_VIRTUAL_FUNCTION ; 
 int /*<<< orphan*/  NET_NAME_UNKNOWN ; 
 int /*<<< orphan*/  RDMA_NETDEV_IPOIB ; 
 int /*<<< orphan*/  ipoib_build_priv (struct net_device*) ; 
 int /*<<< orphan*/  ipoib_mcast_attach ; 
 int /*<<< orphan*/  ipoib_mcast_detach ; 
 int /*<<< orphan*/  ipoib_netdev_default_pf ; 
 int /*<<< orphan*/  ipoib_netdev_ops_pf ; 
 int /*<<< orphan*/  ipoib_netdev_ops_vf ; 
 int /*<<< orphan*/  ipoib_send ; 
 int /*<<< orphan*/  ipoib_setup_common ; 
 int /*<<< orphan*/  kfree (struct ipoib_dev_priv*) ; 
 struct ipoib_dev_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct rdma_netdev* netdev_priv (struct net_device*) ; 
 int rdma_init_netdev (struct ib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 

int ipoib_intf_init(struct ib_device *hca, u8 port, const char *name,
		    struct net_device *dev)
{
	struct rdma_netdev *rn = netdev_priv(dev);
	struct ipoib_dev_priv *priv;
	int rc;

	priv = kzalloc(sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->ca = hca;
	priv->port = port;

	rc = rdma_init_netdev(hca, port, RDMA_NETDEV_IPOIB, name,
			      NET_NAME_UNKNOWN, ipoib_setup_common, dev);
	if (rc) {
		if (rc != -EOPNOTSUPP)
			goto out;

		dev->netdev_ops = &ipoib_netdev_default_pf;
		rn->send = ipoib_send;
		rn->attach_mcast = ipoib_mcast_attach;
		rn->detach_mcast = ipoib_mcast_detach;
		rn->hca = hca;
	}

	priv->rn_ops = dev->netdev_ops;

	if (hca->attrs.device_cap_flags & IB_DEVICE_VIRTUAL_FUNCTION)
		dev->netdev_ops	= &ipoib_netdev_ops_vf;
	else
		dev->netdev_ops	= &ipoib_netdev_ops_pf;

	rn->clnt_priv = priv;
	/*
	 * Only the child register_netdev flows can handle priv_destructor
	 * being set, so we force it to NULL here and handle manually until it
	 * is safe to turn on.
	 */
	priv->next_priv_destructor = dev->priv_destructor;
	dev->priv_destructor = NULL;

	ipoib_build_priv(dev);

	return 0;

out:
	kfree(priv);
	return rc;
}