#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct netdev_queue {int dummy; } ;
struct net_device {int dummy; } ;
struct hns3_nic_priv {int /*<<< orphan*/  state; } ;
struct TYPE_12__ {int tx_bytes; int tx_pkts; int /*<<< orphan*/  restart_queue; int /*<<< orphan*/  io_err_cnt; } ;
struct hns3_enet_ring {int next_to_clean; TYPE_6__ stats; TYPE_5__* tqp; int /*<<< orphan*/  syncp; TYPE_4__* tqp_vector; int /*<<< orphan*/  next_to_use; } ;
struct TYPE_11__ {int /*<<< orphan*/  tqp_index; scalar_t__ io_base; TYPE_2__* handle; } ;
struct TYPE_9__ {int total_bytes; int total_packets; } ;
struct TYPE_10__ {TYPE_3__ tx_group; } ;
struct TYPE_7__ {struct net_device* netdev; } ;
struct TYPE_8__ {TYPE_1__ kinfo; } ;

/* Variables and functions */
 scalar_t__ HNS3_MAX_BD_PER_PKT ; 
 int /*<<< orphan*/  HNS3_NIC_STATE_DOWN ; 
 scalar_t__ HNS3_RING_TX_RING_HEAD_REG ; 
 int /*<<< orphan*/  hns3_nic_reclaim_desc (struct hns3_enet_ring*,int,int*,int*) ; 
 scalar_t__ is_ring_empty (struct hns3_enet_ring*) ; 
 int /*<<< orphan*/  is_valid_clean_head (struct hns3_enet_ring*,int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int,int /*<<< orphan*/ ,int) ; 
 struct netdev_queue* netdev_get_tx_queue (struct net_device*,int /*<<< orphan*/ ) ; 
 struct hns3_nic_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_tx_completed_queue (struct netdev_queue*,int,int) ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 
 scalar_t__ netif_tx_queue_stopped (struct netdev_queue*) ; 
 int /*<<< orphan*/  netif_tx_wake_queue (struct netdev_queue*) ; 
 int readl_relaxed (scalar_t__) ; 
 scalar_t__ ring_space (struct hns3_enet_ring*) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

void hns3_clean_tx_ring(struct hns3_enet_ring *ring)
{
	struct net_device *netdev = ring->tqp->handle->kinfo.netdev;
	struct hns3_nic_priv *priv = netdev_priv(netdev);
	struct netdev_queue *dev_queue;
	int bytes, pkts;
	int head;

	head = readl_relaxed(ring->tqp->io_base + HNS3_RING_TX_RING_HEAD_REG);
	rmb(); /* Make sure head is ready before touch any data */

	if (is_ring_empty(ring) || head == ring->next_to_clean)
		return; /* no data to poll */

	if (unlikely(!is_valid_clean_head(ring, head))) {
		netdev_err(netdev, "wrong head (%d, %d-%d)\n", head,
			   ring->next_to_use, ring->next_to_clean);

		u64_stats_update_begin(&ring->syncp);
		ring->stats.io_err_cnt++;
		u64_stats_update_end(&ring->syncp);
		return;
	}

	bytes = 0;
	pkts = 0;
	hns3_nic_reclaim_desc(ring, head, &bytes, &pkts);

	ring->tqp_vector->tx_group.total_bytes += bytes;
	ring->tqp_vector->tx_group.total_packets += pkts;

	u64_stats_update_begin(&ring->syncp);
	ring->stats.tx_bytes += bytes;
	ring->stats.tx_pkts += pkts;
	u64_stats_update_end(&ring->syncp);

	dev_queue = netdev_get_tx_queue(netdev, ring->tqp->tqp_index);
	netdev_tx_completed_queue(dev_queue, pkts, bytes);

	if (unlikely(pkts && netif_carrier_ok(netdev) &&
		     (ring_space(ring) > HNS3_MAX_BD_PER_PKT))) {
		/* Make sure that anybody stopping the queue after this
		 * sees the new next_to_clean.
		 */
		smp_mb();
		if (netif_tx_queue_stopped(dev_queue) &&
		    !test_bit(HNS3_NIC_STATE_DOWN, &priv->state)) {
			netif_tx_wake_queue(dev_queue);
			ring->stats.restart_queue++;
		}
	}
}