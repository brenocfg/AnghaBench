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
struct vio_dev {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;
struct ibmvnic_adapter {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  VNIC_REMOVED ; 
 int /*<<< orphan*/  VNIC_REMOVING ; 
 int /*<<< orphan*/  dev_attr_failover ; 
 struct net_device* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct ibmvnic_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  release_crq_queue (struct ibmvnic_adapter*) ; 
 int /*<<< orphan*/  release_resources (struct ibmvnic_adapter*) ; 
 int /*<<< orphan*/  release_stats_buffers (struct ibmvnic_adapter*) ; 
 int /*<<< orphan*/  release_stats_token (struct ibmvnic_adapter*) ; 
 int /*<<< orphan*/  release_sub_crqs (struct ibmvnic_adapter*,int) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  unregister_netdevice (struct net_device*) ; 

__attribute__((used)) static int ibmvnic_remove(struct vio_dev *dev)
{
	struct net_device *netdev = dev_get_drvdata(&dev->dev);
	struct ibmvnic_adapter *adapter = netdev_priv(netdev);

	adapter->state = VNIC_REMOVING;
	rtnl_lock();
	unregister_netdevice(netdev);

	release_resources(adapter);
	release_sub_crqs(adapter, 1);
	release_crq_queue(adapter);

	release_stats_token(adapter);
	release_stats_buffers(adapter);

	adapter->state = VNIC_REMOVED;

	rtnl_unlock();
	device_remove_file(&dev->dev, &dev_attr_failover);
	free_netdev(netdev);
	dev_set_drvdata(&dev->dev, NULL);

	return 0;
}