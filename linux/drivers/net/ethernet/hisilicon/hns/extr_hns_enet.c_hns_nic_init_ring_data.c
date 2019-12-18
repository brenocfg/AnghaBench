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
struct hns_nic_ring_data {int queue_index; TYPE_2__* ring; int /*<<< orphan*/  napi; int /*<<< orphan*/  fini_process; int /*<<< orphan*/  ex_process; int /*<<< orphan*/  poll_one; } ;
struct hns_nic_priv {int /*<<< orphan*/  netdev; struct hns_nic_ring_data* ring_data; int /*<<< orphan*/  enet_ver; struct hnae_handle* ae_handle; } ;
struct hnae_handle {int q_num; TYPE_1__** qs; } ;
struct TYPE_4__ {void* irq_init_flag; } ;
struct TYPE_3__ {TYPE_2__ rx_ring; TYPE_2__ tx_ring; } ;

/* Variables and functions */
 int AE_IS_VER1 (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NAPI_POLL_WEIGHT ; 
 int NIC_MAX_Q_PER_VF ; 
 void* RCB_IRQ_NOT_INITED ; 
 int /*<<< orphan*/  array3_size (int,int,int) ; 
 int /*<<< orphan*/  hns_nic_common_poll ; 
 int /*<<< orphan*/  hns_nic_rx_fini_pro ; 
 int /*<<< orphan*/  hns_nic_rx_fini_pro_v2 ; 
 int /*<<< orphan*/  hns_nic_rx_poll_one ; 
 int /*<<< orphan*/  hns_nic_rx_up_pro ; 
 int /*<<< orphan*/  hns_nic_tx_fini_pro ; 
 int /*<<< orphan*/  hns_nic_tx_fini_pro_v2 ; 
 int /*<<< orphan*/  hns_nic_tx_poll_one ; 
 struct hns_nic_ring_data* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  netif_napi_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hns_nic_init_ring_data(struct hns_nic_priv *priv)
{
	struct hnae_handle *h = priv->ae_handle;
	struct hns_nic_ring_data *rd;
	bool is_ver1 = AE_IS_VER1(priv->enet_ver);
	int i;

	if (h->q_num > NIC_MAX_Q_PER_VF) {
		netdev_err(priv->netdev, "too much queue (%d)\n", h->q_num);
		return -EINVAL;
	}

	priv->ring_data = kzalloc(array3_size(h->q_num,
					      sizeof(*priv->ring_data), 2),
				  GFP_KERNEL);
	if (!priv->ring_data)
		return -ENOMEM;

	for (i = 0; i < h->q_num; i++) {
		rd = &priv->ring_data[i];
		rd->queue_index = i;
		rd->ring = &h->qs[i]->tx_ring;
		rd->poll_one = hns_nic_tx_poll_one;
		rd->fini_process = is_ver1 ? hns_nic_tx_fini_pro :
			hns_nic_tx_fini_pro_v2;

		netif_napi_add(priv->netdev, &rd->napi,
			       hns_nic_common_poll, NAPI_POLL_WEIGHT);
		rd->ring->irq_init_flag = RCB_IRQ_NOT_INITED;
	}
	for (i = h->q_num; i < h->q_num * 2; i++) {
		rd = &priv->ring_data[i];
		rd->queue_index = i - h->q_num;
		rd->ring = &h->qs[i - h->q_num]->rx_ring;
		rd->poll_one = hns_nic_rx_poll_one;
		rd->ex_process = hns_nic_rx_up_pro;
		rd->fini_process = is_ver1 ? hns_nic_rx_fini_pro :
			hns_nic_rx_fini_pro_v2;

		netif_napi_add(priv->netdev, &rd->napi,
			       hns_nic_common_poll, NAPI_POLL_WEIGHT);
		rd->ring->irq_init_flag = RCB_IRQ_NOT_INITED;
	}

	return 0;
}