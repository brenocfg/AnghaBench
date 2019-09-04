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
typedef  size_t u32 ;
struct netdev_queue {int dummy; } ;
struct net_device {int dummy; } ;
struct hns3_nic_priv {TYPE_1__* ring_data; } ;
struct hns3_enet_ring {int dummy; } ;
struct TYPE_4__ {size_t num_tqps; struct net_device* netdev; } ;
struct hnae3_handle {TYPE_2__ kinfo; } ;
struct TYPE_3__ {struct hns3_enet_ring* ring; int /*<<< orphan*/  queue_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  hns3_clear_rx_ring (struct hns3_enet_ring*) ; 
 int /*<<< orphan*/  hns3_clear_tx_ring (struct hns3_enet_ring*) ; 
 struct netdev_queue* netdev_get_tx_queue (struct net_device*,int /*<<< orphan*/ ) ; 
 struct hns3_nic_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_tx_reset_queue (struct netdev_queue*) ; 

__attribute__((used)) static void hns3_clear_all_ring(struct hnae3_handle *h)
{
	struct net_device *ndev = h->kinfo.netdev;
	struct hns3_nic_priv *priv = netdev_priv(ndev);
	u32 i;

	for (i = 0; i < h->kinfo.num_tqps; i++) {
		struct netdev_queue *dev_queue;
		struct hns3_enet_ring *ring;

		ring = priv->ring_data[i].ring;
		hns3_clear_tx_ring(ring);
		dev_queue = netdev_get_tx_queue(ndev,
						priv->ring_data[i].queue_index);
		netdev_tx_reset_queue(dev_queue);

		ring = priv->ring_data[i + h->kinfo.num_tqps].ring;
		/* Continue to clear other rings even if clearing some
		 * rings failed.
		 */
		hns3_clear_rx_ring(ring);
	}
}