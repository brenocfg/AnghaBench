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
struct netdev_queue {unsigned long trans_start; } ;
struct net_device {int real_num_tx_queues; int num_tx_queues; scalar_t__ watchdog_timeo; } ;
struct hns3_nic_priv {int /*<<< orphan*/  tx_timeout_count; TYPE_1__* ring_data; } ;
struct hns3_enet_ring {TYPE_3__* tqp_vector; int /*<<< orphan*/  next_to_clean; int /*<<< orphan*/  next_to_use; TYPE_2__* tqp; } ;
struct TYPE_6__ {int /*<<< orphan*/  mask_addr; } ;
struct TYPE_5__ {scalar_t__ io_base; } ;
struct TYPE_4__ {struct hns3_enet_ring* ring; } ;

/* Variables and functions */
 scalar_t__ HNS3_RING_TX_RING_HEAD_REG ; 
 scalar_t__ HNS3_RING_TX_RING_TAIL_REG ; 
 int /*<<< orphan*/  jiffies ; 
 struct netdev_queue* netdev_get_tx_queue (struct net_device*,int) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int /*<<< orphan*/ ,...) ; 
 struct hns3_nic_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_xmit_stopped (struct netdev_queue*) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int readl_relaxed (scalar_t__) ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static bool hns3_get_tx_timeo_queue_info(struct net_device *ndev)
{
	struct hns3_nic_priv *priv = netdev_priv(ndev);
	struct hns3_enet_ring *tx_ring = NULL;
	int timeout_queue = 0;
	int hw_head, hw_tail;
	int i;

	/* Find the stopped queue the same way the stack does */
	for (i = 0; i < ndev->real_num_tx_queues; i++) {
		struct netdev_queue *q;
		unsigned long trans_start;

		q = netdev_get_tx_queue(ndev, i);
		trans_start = q->trans_start;
		if (netif_xmit_stopped(q) &&
		    time_after(jiffies,
			       (trans_start + ndev->watchdog_timeo))) {
			timeout_queue = i;
			break;
		}
	}

	if (i == ndev->num_tx_queues) {
		netdev_info(ndev,
			    "no netdev TX timeout queue found, timeout count: %llu\n",
			    priv->tx_timeout_count);
		return false;
	}

	tx_ring = priv->ring_data[timeout_queue].ring;

	hw_head = readl_relaxed(tx_ring->tqp->io_base +
				HNS3_RING_TX_RING_HEAD_REG);
	hw_tail = readl_relaxed(tx_ring->tqp->io_base +
				HNS3_RING_TX_RING_TAIL_REG);
	netdev_info(ndev,
		    "tx_timeout count: %llu, queue id: %d, SW_NTU: 0x%x, SW_NTC: 0x%x, HW_HEAD: 0x%x, HW_TAIL: 0x%x, INT: 0x%x\n",
		    priv->tx_timeout_count,
		    timeout_queue,
		    tx_ring->next_to_use,
		    tx_ring->next_to_clean,
		    hw_head,
		    hw_tail,
		    readl(tx_ring->tqp_vector->mask_addr));

	return true;
}