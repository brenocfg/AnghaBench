#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hns_nic_priv {TYPE_2__* ring_data; struct hnae_handle* ae_handle; } ;
struct hnae_handle {int q_num; } ;
struct TYPE_5__ {TYPE_1__* ring; int /*<<< orphan*/  napi; } ;
struct TYPE_4__ {scalar_t__ irq_init_flag; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 scalar_t__ RCB_IRQ_INITED ; 
 scalar_t__ RCB_IRQ_NOT_INITED ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  irq_set_affinity_hint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hns_nic_uninit_ring_data(struct hns_nic_priv *priv)
{
	struct hnae_handle *h = priv->ae_handle;
	int i;

	for (i = 0; i < h->q_num * 2; i++) {
		netif_napi_del(&priv->ring_data[i].napi);
		if (priv->ring_data[i].ring->irq_init_flag == RCB_IRQ_INITED) {
			(void)irq_set_affinity_hint(
				priv->ring_data[i].ring->irq,
				NULL);
			free_irq(priv->ring_data[i].ring->irq,
				 &priv->ring_data[i]);
		}

		priv->ring_data[i].ring->irq_init_flag = RCB_IRQ_NOT_INITED;
	}
	kfree(priv->ring_data);
}