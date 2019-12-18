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
struct hns3_nic_priv {int vector_num; int /*<<< orphan*/  netdev; struct hns3_enet_tqp_vector* tqp_vector; } ;
struct TYPE_4__ {struct hns3_enet_ring* ring; } ;
struct hns3_enet_tqp_vector {int /*<<< orphan*/  affinity_mask; TYPE_2__ tx_group; } ;
struct hns3_enet_ring {struct hns3_enet_ring* next; TYPE_1__* tqp; } ;
struct TYPE_3__ {int /*<<< orphan*/  tqp_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int netif_set_xps_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns3_config_xps(struct hns3_nic_priv *priv)
{
	int i;

	for (i = 0; i < priv->vector_num; i++) {
		struct hns3_enet_tqp_vector *tqp_vector = &priv->tqp_vector[i];
		struct hns3_enet_ring *ring = tqp_vector->tx_group.ring;

		while (ring) {
			int ret;

			ret = netif_set_xps_queue(priv->netdev,
						  &tqp_vector->affinity_mask,
						  ring->tqp->tqp_index);
			if (ret)
				netdev_warn(priv->netdev,
					    "set xps queue failed: %d", ret);

			ring = ring->next;
		}
	}
}