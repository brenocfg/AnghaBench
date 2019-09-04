#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct ixgbe_ring {int /*<<< orphan*/ * netdev; struct ixgbe_q_vector* q_vector; } ;
struct ixgbe_q_vector {int /*<<< orphan*/  napi; } ;
struct ixgbe_fwd_adapter {unsigned int rx_base_queue; int /*<<< orphan*/  pool; TYPE_1__* netdev; } ;
struct ixgbe_adapter {unsigned int num_rx_queues_per_pool; int /*<<< orphan*/  fwd_bitmask; int /*<<< orphan*/  netdev; struct ixgbe_ring** rx_ring; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMDQ_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_del_mac_filter (struct ixgbe_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ixgbe_fwd_adapter*) ; 
 int /*<<< orphan*/  napi_synchronize (int /*<<< orphan*/ *) ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_set_sb_channel (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_unbind_sb_channel (struct net_device*,TYPE_1__*) ; 
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void ixgbe_fwd_del(struct net_device *pdev, void *priv)
{
	struct ixgbe_fwd_adapter *accel = priv;
	struct ixgbe_adapter *adapter = netdev_priv(pdev);
	unsigned int rxbase = accel->rx_base_queue;
	unsigned int i;

	/* delete unicast filter associated with offloaded interface */
	ixgbe_del_mac_filter(adapter, accel->netdev->dev_addr,
			     VMDQ_P(accel->pool));

	/* Allow remaining Rx packets to get flushed out of the
	 * Rx FIFO before we drop the netdev for the ring.
	 */
	usleep_range(10000, 20000);

	for (i = 0; i < adapter->num_rx_queues_per_pool; i++) {
		struct ixgbe_ring *ring = adapter->rx_ring[rxbase + i];
		struct ixgbe_q_vector *qv = ring->q_vector;

		/* Make sure we aren't processing any packets and clear
		 * netdev to shut down the ring.
		 */
		if (netif_running(adapter->netdev))
			napi_synchronize(&qv->napi);
		ring->netdev = NULL;
	}

	/* unbind the queues and drop the subordinate channel config */
	netdev_unbind_sb_channel(pdev, accel->netdev);
	netdev_set_sb_channel(accel->netdev, 0);

	clear_bit(accel->pool, adapter->fwd_bitmask);
	kfree(accel);
}