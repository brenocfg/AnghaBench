#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct nfp_repr {TYPE_3__* dst; struct nfp_port* port; } ;
struct nfp_port {int dummy; } ;
struct nfp_app {int dummy; } ;
struct net_device {int /*<<< orphan*/  hw_features; int /*<<< orphan*/  features; int /*<<< orphan*/  priv_flags; int /*<<< orphan*/  max_mtu; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; } ;
struct dst_entry {int dummy; } ;
struct TYPE_4__ {struct net_device* lower_dev; int /*<<< orphan*/  port_id; } ;
struct TYPE_5__ {TYPE_1__ port_info; } ;
struct TYPE_6__ {TYPE_2__ u; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IFF_DISABLE_NETPOLL ; 
 int /*<<< orphan*/  METADATA_HW_PORT_MUX ; 
 int /*<<< orphan*/  NETIF_F_HW_TC ; 
 int /*<<< orphan*/  SWITCHDEV_SET_OPS (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 
 TYPE_3__* metadata_dst_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nfp_repr* netdev_priv (struct net_device*) ; 
 scalar_t__ nfp_app_has_tc (struct nfp_app*) ; 
 int /*<<< orphan*/  nfp_app_repr_clean (struct nfp_app*,struct net_device*) ; 
 int nfp_app_repr_init (struct nfp_app*,struct net_device*) ; 
 int /*<<< orphan*/  nfp_port_ethtool_ops ; 
 int /*<<< orphan*/  nfp_port_switchdev_ops ; 
 int /*<<< orphan*/  nfp_repr_netdev_ops ; 
 int /*<<< orphan*/  nfp_repr_set_lockdep_class (struct net_device*) ; 
 int register_netdev (struct net_device*) ; 

int nfp_repr_init(struct nfp_app *app, struct net_device *netdev,
		  u32 cmsg_port_id, struct nfp_port *port,
		  struct net_device *pf_netdev)
{
	struct nfp_repr *repr = netdev_priv(netdev);
	int err;

	nfp_repr_set_lockdep_class(netdev);

	repr->port = port;
	repr->dst = metadata_dst_alloc(0, METADATA_HW_PORT_MUX, GFP_KERNEL);
	if (!repr->dst)
		return -ENOMEM;
	repr->dst->u.port_info.port_id = cmsg_port_id;
	repr->dst->u.port_info.lower_dev = pf_netdev;

	netdev->netdev_ops = &nfp_repr_netdev_ops;
	netdev->ethtool_ops = &nfp_port_ethtool_ops;

	netdev->max_mtu = pf_netdev->max_mtu;

	SWITCHDEV_SET_OPS(netdev, &nfp_port_switchdev_ops);

	netdev->priv_flags |= IFF_DISABLE_NETPOLL;

	if (nfp_app_has_tc(app)) {
		netdev->features |= NETIF_F_HW_TC;
		netdev->hw_features |= NETIF_F_HW_TC;
	}

	err = nfp_app_repr_init(app, netdev);
	if (err)
		goto err_clean;

	err = register_netdev(netdev);
	if (err)
		goto err_repr_clean;

	return 0;

err_repr_clean:
	nfp_app_repr_clean(app, netdev);
err_clean:
	dst_release((struct dst_entry *)repr->dst);
	return err;
}