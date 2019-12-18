#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct hns3_nic_priv {TYPE_3__* ring_data; } ;
struct hns3_enet_ring {int desc_num; scalar_t__ next_to_use; scalar_t__ next_to_clean; } ;
struct TYPE_8__ {int num_tqps; struct net_device* netdev; } ;
struct hnae3_handle {TYPE_4__ kinfo; TYPE_2__* ae_algo; } ;
struct TYPE_7__ {struct hns3_enet_ring* ring; } ;
struct TYPE_6__ {TYPE_1__* ops; } ;
struct TYPE_5__ {int (* reset_queue ) (struct hnae3_handle*,int) ;} ;

/* Variables and functions */
 int hns3_clear_rx_ring (struct hns3_enet_ring*) ; 
 int /*<<< orphan*/  hns3_clear_tx_ring (struct hns3_enet_ring*) ; 
 int /*<<< orphan*/  hns3_init_ring_hw (struct hns3_enet_ring*) ; 
 int /*<<< orphan*/  hns3_init_tx_ring_tc (struct hns3_nic_priv*) ; 
 int /*<<< orphan*/  hns3_reuse_buffer (struct hns3_enet_ring*,int) ; 
 struct hns3_nic_priv* netdev_priv (struct net_device*) ; 
 int stub1 (struct hnae3_handle*,int) ; 

int hns3_nic_reset_all_ring(struct hnae3_handle *h)
{
	struct net_device *ndev = h->kinfo.netdev;
	struct hns3_nic_priv *priv = netdev_priv(ndev);
	struct hns3_enet_ring *rx_ring;
	int i, j;
	int ret;

	for (i = 0; i < h->kinfo.num_tqps; i++) {
		ret = h->ae_algo->ops->reset_queue(h, i);
		if (ret)
			return ret;

		hns3_init_ring_hw(priv->ring_data[i].ring);

		/* We need to clear tx ring here because self test will
		 * use the ring and will not run down before up
		 */
		hns3_clear_tx_ring(priv->ring_data[i].ring);
		priv->ring_data[i].ring->next_to_clean = 0;
		priv->ring_data[i].ring->next_to_use = 0;

		rx_ring = priv->ring_data[i + h->kinfo.num_tqps].ring;
		hns3_init_ring_hw(rx_ring);
		ret = hns3_clear_rx_ring(rx_ring);
		if (ret)
			return ret;

		/* We can not know the hardware head and tail when this
		 * function is called in reset flow, so we reuse all desc.
		 */
		for (j = 0; j < rx_ring->desc_num; j++)
			hns3_reuse_buffer(rx_ring, j);

		rx_ring->next_to_clean = 0;
		rx_ring->next_to_use = 0;
	}

	hns3_init_tx_ring_tc(priv);

	return 0;
}