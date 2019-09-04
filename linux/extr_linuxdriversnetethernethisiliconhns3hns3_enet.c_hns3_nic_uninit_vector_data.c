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
struct hns3_nic_priv {int vector_num; struct hns3_enet_tqp_vector* tqp_vector; TYPE_4__* ring_data; struct hnae3_handle* ae_handle; } ;
struct hns3_enet_tqp_vector {scalar_t__ irq_init_flag; int /*<<< orphan*/  napi; int /*<<< orphan*/  tx_group; int /*<<< orphan*/  rx_group; int /*<<< orphan*/  vector_irq; } ;
struct hnae3_ring_chain_node {int dummy; } ;
struct hnae3_handle {TYPE_2__* ae_algo; } ;
struct TYPE_8__ {TYPE_3__* ring; } ;
struct TYPE_7__ {void* irq_init_flag; } ;
struct TYPE_6__ {TYPE_1__* ops; } ;
struct TYPE_5__ {int (* unmap_ring_from_vector ) (struct hnae3_handle*,int /*<<< orphan*/ ,struct hnae3_ring_chain_node*) ;} ;

/* Variables and functions */
 scalar_t__ HNS3_VECTOR_INITED ; 
 void* HNS3_VECTOR_NOT_INITED ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct hns3_enet_tqp_vector*) ; 
 int /*<<< orphan*/  hns3_clear_ring_group (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hns3_free_vector_ring_chain (struct hns3_enet_tqp_vector*,struct hnae3_ring_chain_node*) ; 
 int hns3_get_vector_ring_chain (struct hns3_enet_tqp_vector*,struct hnae3_ring_chain_node*) ; 
 int /*<<< orphan*/  irq_set_affinity_hint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_set_affinity_notifier (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 
 int stub1 (struct hnae3_handle*,int /*<<< orphan*/ ,struct hnae3_ring_chain_node*) ; 

__attribute__((used)) static int hns3_nic_uninit_vector_data(struct hns3_nic_priv *priv)
{
	struct hnae3_ring_chain_node vector_ring_chain;
	struct hnae3_handle *h = priv->ae_handle;
	struct hns3_enet_tqp_vector *tqp_vector;
	int i, ret;

	for (i = 0; i < priv->vector_num; i++) {
		tqp_vector = &priv->tqp_vector[i];

		ret = hns3_get_vector_ring_chain(tqp_vector,
						 &vector_ring_chain);
		if (ret)
			return ret;

		ret = h->ae_algo->ops->unmap_ring_from_vector(h,
			tqp_vector->vector_irq, &vector_ring_chain);
		if (ret)
			return ret;

		hns3_free_vector_ring_chain(tqp_vector, &vector_ring_chain);

		if (tqp_vector->irq_init_flag == HNS3_VECTOR_INITED) {
			irq_set_affinity_notifier(tqp_vector->vector_irq,
						  NULL);
			irq_set_affinity_hint(tqp_vector->vector_irq, NULL);
			free_irq(tqp_vector->vector_irq, tqp_vector);
			tqp_vector->irq_init_flag = HNS3_VECTOR_NOT_INITED;
		}

		priv->ring_data[i].ring->irq_init_flag = HNS3_VECTOR_NOT_INITED;
		hns3_clear_ring_group(&tqp_vector->rx_group);
		hns3_clear_ring_group(&tqp_vector->tx_group);
		netif_napi_del(&priv->tqp_vector[i].napi);
	}

	return 0;
}