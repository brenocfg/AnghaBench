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
struct vio_device_id {int dummy; } ;
struct vio_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; int /*<<< orphan*/  unit_address; } ;
struct net_device {unsigned char* dev_addr; void* max_mtu; void* min_mtu; void* mtu; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  irq; } ;
struct ibmvnic_adapter {unsigned char* mac_addr; int resetting; int mac_change_pending; void* req_mtu; void* min_mtu; void* max_mtu; int wait_for_reset; int /*<<< orphan*/  state; int /*<<< orphan*/  init_done; int /*<<< orphan*/  rwi_lock; int /*<<< orphan*/  rwi_list; int /*<<< orphan*/  ibmvnic_reset; int /*<<< orphan*/  stats_lock; struct net_device* netdev; struct vio_dev* vdev; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOMEM ; 
 void* ETH_HLEN ; 
 int /*<<< orphan*/  IBMVNIC_MAX_QUEUES ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VETH_MAC_ADDR ; 
 int /*<<< orphan*/  VNIC_PROBED ; 
 int /*<<< orphan*/  VNIC_PROBING ; 
 int /*<<< orphan*/  __ibmvnic_reset ; 
 struct net_device* alloc_etherdev_mq (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_attr_failover ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct net_device*) ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ether_addr_copy (unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  ibmvnic_ethtool_ops ; 
 int ibmvnic_init (struct ibmvnic_adapter*) ; 
 int /*<<< orphan*/  ibmvnic_netdev_ops ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int init_crq_queue (struct ibmvnic_adapter*) ; 
 int init_stats_buffers (struct ibmvnic_adapter*) ; 
 int init_stats_token (struct ibmvnic_adapter*) ; 
 struct ibmvnic_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  release_crq_queue (struct ibmvnic_adapter*) ; 
 int /*<<< orphan*/  release_stats_buffers (struct ibmvnic_adapter*) ; 
 int /*<<< orphan*/  release_stats_token (struct ibmvnic_adapter*) ; 
 int /*<<< orphan*/  release_sub_crqs (struct ibmvnic_adapter*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 scalar_t__ vio_get_attribute (struct vio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ibmvnic_probe(struct vio_dev *dev, const struct vio_device_id *id)
{
	struct ibmvnic_adapter *adapter;
	struct net_device *netdev;
	unsigned char *mac_addr_p;
	int rc;

	dev_dbg(&dev->dev, "entering ibmvnic_probe for UA 0x%x\n",
		dev->unit_address);

	mac_addr_p = (unsigned char *)vio_get_attribute(dev,
							VETH_MAC_ADDR, NULL);
	if (!mac_addr_p) {
		dev_err(&dev->dev,
			"(%s:%3.3d) ERROR: Can't find MAC_ADDR attribute\n",
			__FILE__, __LINE__);
		return 0;
	}

	netdev = alloc_etherdev_mq(sizeof(struct ibmvnic_adapter),
				   IBMVNIC_MAX_QUEUES);
	if (!netdev)
		return -ENOMEM;

	adapter = netdev_priv(netdev);
	adapter->state = VNIC_PROBING;
	dev_set_drvdata(&dev->dev, netdev);
	adapter->vdev = dev;
	adapter->netdev = netdev;

	ether_addr_copy(adapter->mac_addr, mac_addr_p);
	ether_addr_copy(netdev->dev_addr, adapter->mac_addr);
	netdev->irq = dev->irq;
	netdev->netdev_ops = &ibmvnic_netdev_ops;
	netdev->ethtool_ops = &ibmvnic_ethtool_ops;
	SET_NETDEV_DEV(netdev, &dev->dev);

	spin_lock_init(&adapter->stats_lock);

	INIT_WORK(&adapter->ibmvnic_reset, __ibmvnic_reset);
	INIT_LIST_HEAD(&adapter->rwi_list);
	spin_lock_init(&adapter->rwi_lock);
	init_completion(&adapter->init_done);
	adapter->resetting = false;

	adapter->mac_change_pending = false;

	do {
		rc = init_crq_queue(adapter);
		if (rc) {
			dev_err(&dev->dev, "Couldn't initialize crq. rc=%d\n",
				rc);
			goto ibmvnic_init_fail;
		}

		rc = ibmvnic_init(adapter);
		if (rc && rc != EAGAIN)
			goto ibmvnic_init_fail;
	} while (rc == EAGAIN);

	rc = init_stats_buffers(adapter);
	if (rc)
		goto ibmvnic_init_fail;

	rc = init_stats_token(adapter);
	if (rc)
		goto ibmvnic_stats_fail;

	netdev->mtu = adapter->req_mtu - ETH_HLEN;
	netdev->min_mtu = adapter->min_mtu - ETH_HLEN;
	netdev->max_mtu = adapter->max_mtu - ETH_HLEN;

	rc = device_create_file(&dev->dev, &dev_attr_failover);
	if (rc)
		goto ibmvnic_dev_file_err;

	netif_carrier_off(netdev);
	rc = register_netdev(netdev);
	if (rc) {
		dev_err(&dev->dev, "failed to register netdev rc=%d\n", rc);
		goto ibmvnic_register_fail;
	}
	dev_info(&dev->dev, "ibmvnic registered\n");

	adapter->state = VNIC_PROBED;

	adapter->wait_for_reset = false;

	return 0;

ibmvnic_register_fail:
	device_remove_file(&dev->dev, &dev_attr_failover);

ibmvnic_dev_file_err:
	release_stats_token(adapter);

ibmvnic_stats_fail:
	release_stats_buffers(adapter);

ibmvnic_init_fail:
	release_sub_crqs(adapter, 1);
	release_crq_queue(adapter);
	free_netdev(netdev);

	return rc;
}