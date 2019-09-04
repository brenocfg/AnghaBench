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
struct rdma_netdev {int /*<<< orphan*/  (* free_rdma_netdev ) (struct net_device*) ;} ;
struct opa_vnic_adapter {int /*<<< orphan*/  mactbl_lock; int /*<<< orphan*/  lock; struct net_device* netdev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct opa_vnic_adapter*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 struct rdma_netdev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  opa_vnic_release_mac_tbl (struct opa_vnic_adapter*) ; 
 int /*<<< orphan*/  stub1 (struct net_device*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 
 int /*<<< orphan*/  v_info (char*) ; 

void opa_vnic_rem_netdev(struct opa_vnic_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	struct rdma_netdev *rn = netdev_priv(netdev);

	v_info("removing\n");
	unregister_netdev(netdev);
	opa_vnic_release_mac_tbl(adapter);
	mutex_destroy(&adapter->lock);
	mutex_destroy(&adapter->mactbl_lock);
	kfree(adapter);
	rn->free_rdma_netdev(netdev);
}