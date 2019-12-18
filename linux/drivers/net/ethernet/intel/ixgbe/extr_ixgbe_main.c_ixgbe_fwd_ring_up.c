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
typedef  int u16 ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct ixgbe_fwd_adapter {int pool; int rx_base_queue; int tx_base_queue; struct net_device* netdev; } ;
struct ixgbe_adapter {int num_rx_queues_per_pool; int /*<<< orphan*/  fwd_bitmask; int /*<<< orphan*/  netdev; TYPE_2__** rx_ring; int /*<<< orphan*/  num_rx_pools; TYPE_1__* ring_feature; } ;
struct TYPE_4__ {struct net_device* netdev; } ;
struct TYPE_3__ {int indices; } ;

/* Variables and functions */
 size_t RING_F_RSS ; 
 int /*<<< orphan*/  VMDQ_P (int) ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int ixgbe_add_mac_filter (struct ixgbe_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ixgbe_fwd_adapter*) ; 
 int /*<<< orphan*/  macvlan_release_l2fw_offload (struct net_device*) ; 
 int /*<<< orphan*/  netdev_bind_sb_channel_queue (int /*<<< orphan*/ ,struct net_device*,int,int,int) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int netdev_get_num_tc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_set_sb_channel (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_unbind_sb_channel (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int ixgbe_fwd_ring_up(struct ixgbe_adapter *adapter,
			     struct ixgbe_fwd_adapter *accel)
{
	u16 rss_i = adapter->ring_feature[RING_F_RSS].indices;
	int num_tc = netdev_get_num_tc(adapter->netdev);
	struct net_device *vdev = accel->netdev;
	int i, baseq, err;

	baseq = accel->pool * adapter->num_rx_queues_per_pool;
	netdev_dbg(vdev, "pool %i:%i queues %i:%i\n",
		   accel->pool, adapter->num_rx_pools,
		   baseq, baseq + adapter->num_rx_queues_per_pool);

	accel->rx_base_queue = baseq;
	accel->tx_base_queue = baseq;

	/* record configuration for macvlan interface in vdev */
	for (i = 0; i < num_tc; i++)
		netdev_bind_sb_channel_queue(adapter->netdev, vdev,
					     i, rss_i, baseq + (rss_i * i));

	for (i = 0; i < adapter->num_rx_queues_per_pool; i++)
		adapter->rx_ring[baseq + i]->netdev = vdev;

	/* Guarantee all rings are updated before we update the
	 * MAC address filter.
	 */
	wmb();

	/* ixgbe_add_mac_filter will return an index if it succeeds, so we
	 * need to only treat it as an error value if it is negative.
	 */
	err = ixgbe_add_mac_filter(adapter, vdev->dev_addr,
				   VMDQ_P(accel->pool));
	if (err >= 0)
		return 0;

	/* if we cannot add the MAC rule then disable the offload */
	macvlan_release_l2fw_offload(vdev);

	for (i = 0; i < adapter->num_rx_queues_per_pool; i++)
		adapter->rx_ring[baseq + i]->netdev = NULL;

	netdev_err(vdev, "L2FW offload disabled due to L2 filter error\n");

	/* unbind the queues and drop the subordinate channel config */
	netdev_unbind_sb_channel(adapter->netdev, vdev);
	netdev_set_sb_channel(vdev, 0);

	clear_bit(accel->pool, adapter->fwd_bitmask);
	kfree(accel);

	return err;
}