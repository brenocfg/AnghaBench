#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
struct rdma_netdev {int /*<<< orphan*/  (* free_rdma_netdev ) (struct net_device*) ;void* port_num; struct ib_device* hca; struct opa_vnic_adapter* clnt_priv; } ;
struct opa_vnic_adapter {int /*<<< orphan*/  mactbl_lock; int /*<<< orphan*/  lock; int /*<<< orphan*/  stats_lock; int /*<<< orphan*/ * rn_ops; void* vport_num; void* port_num; struct ib_device* ibdev; struct net_device* netdev; } ;
struct net_device {int /*<<< orphan*/  hard_header_len; int /*<<< orphan*/  priv_flags; int /*<<< orphan*/ * netdev_ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct TYPE_3__ {struct net_device* (* alloc_rdma_netdev ) (struct ib_device*,void*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct ib_device {TYPE_2__ dev; TYPE_1__ ops; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct opa_vnic_adapter* ERR_CAST (struct net_device*) ; 
 struct opa_vnic_adapter* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IFF_LIVE_ADDR_CHANGE ; 
 scalar_t__ IS_ERR (struct net_device*) ; 
 int /*<<< orphan*/  NET_NAME_UNKNOWN ; 
 scalar_t__ OPA_VNIC_SKB_HEADROOM ; 
 int /*<<< orphan*/  RDMA_NETDEV_OPA_VNIC ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_setup ; 
 int /*<<< orphan*/  kfree (struct opa_vnic_adapter*) ; 
 struct opa_vnic_adapter* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct rdma_netdev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_dormant_on (struct net_device*) ; 
 int /*<<< orphan*/  opa_netdev_ops ; 
 int /*<<< orphan*/  opa_vnic_set_ethtool_ops (struct net_device*) ; 
 int /*<<< orphan*/  opa_vnic_set_pod_values (struct opa_vnic_adapter*) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 struct net_device* stub1 (struct ib_device*,void*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct net_device*) ; 
 int /*<<< orphan*/  v_info (char*) ; 

struct opa_vnic_adapter *opa_vnic_add_netdev(struct ib_device *ibdev,
					     u8 port_num, u8 vport_num)
{
	struct opa_vnic_adapter *adapter;
	struct net_device *netdev;
	struct rdma_netdev *rn;
	int rc;

	netdev = ibdev->ops.alloc_rdma_netdev(ibdev, port_num,
					      RDMA_NETDEV_OPA_VNIC,
					      "veth%d", NET_NAME_UNKNOWN,
					      ether_setup);
	if (!netdev)
		return ERR_PTR(-ENOMEM);
	else if (IS_ERR(netdev))
		return ERR_CAST(netdev);

	rn = netdev_priv(netdev);
	adapter = kzalloc(sizeof(*adapter), GFP_KERNEL);
	if (!adapter) {
		rc = -ENOMEM;
		goto adapter_err;
	}

	rn->clnt_priv = adapter;
	rn->hca = ibdev;
	rn->port_num = port_num;
	adapter->netdev = netdev;
	adapter->ibdev = ibdev;
	adapter->port_num = port_num;
	adapter->vport_num = vport_num;
	adapter->rn_ops = netdev->netdev_ops;

	netdev->netdev_ops = &opa_netdev_ops;
	netdev->priv_flags |= IFF_LIVE_ADDR_CHANGE;
	netdev->hard_header_len += OPA_VNIC_SKB_HEADROOM;
	mutex_init(&adapter->lock);
	mutex_init(&adapter->mactbl_lock);
	spin_lock_init(&adapter->stats_lock);

	SET_NETDEV_DEV(netdev, ibdev->dev.parent);

	opa_vnic_set_ethtool_ops(netdev);

	opa_vnic_set_pod_values(adapter);

	rc = register_netdev(netdev);
	if (rc)
		goto netdev_err;

	netif_carrier_off(netdev);
	netif_dormant_on(netdev);
	v_info("initialized\n");

	return adapter;
netdev_err:
	mutex_destroy(&adapter->lock);
	mutex_destroy(&adapter->mactbl_lock);
	kfree(adapter);
adapter_err:
	rn->free_rdma_netdev(netdev);

	return ERR_PTR(rc);
}