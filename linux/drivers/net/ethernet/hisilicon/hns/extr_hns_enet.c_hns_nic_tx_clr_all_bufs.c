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
struct netdev_queue {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {struct net_device* dev; } ;
struct hns_nic_ring_data {int /*<<< orphan*/  queue_index; TYPE_1__ napi; struct hnae_ring* ring; } ;
struct hnae_ring {int next_to_use; int next_to_clean; } ;

/* Variables and functions */
 int /*<<< orphan*/  hns_nic_reclaim_one_desc (struct hnae_ring*,int*,int*) ; 
 struct netdev_queue* netdev_get_tx_queue (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_tx_reset_queue (struct netdev_queue*) ; 

__attribute__((used)) static void hns_nic_tx_clr_all_bufs(struct hns_nic_ring_data *ring_data)
{
	struct hnae_ring *ring = ring_data->ring;
	struct net_device *ndev = ring_data->napi.dev;
	struct netdev_queue *dev_queue;
	int head;
	int bytes, pkts;

	head = ring->next_to_use; /* ntu :soft setted ring position*/
	bytes = 0;
	pkts = 0;
	while (head != ring->next_to_clean)
		hns_nic_reclaim_one_desc(ring, &bytes, &pkts);

	dev_queue = netdev_get_tx_queue(ndev, ring_data->queue_index);
	netdev_tx_reset_queue(dev_queue);
}