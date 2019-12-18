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
struct hns_nic_ring_data {TYPE_2__* ring; int /*<<< orphan*/  mask; int /*<<< orphan*/  queue_index; } ;
struct hns_nic_priv {TYPE_1__* netdev; struct hns_nic_ring_data* ring_data; struct hnae_handle* ae_handle; } ;
struct hnae_handle {int q_num; } ;
struct TYPE_5__ {scalar_t__ irq_init_flag; char* ring_name; int /*<<< orphan*/  irq; } ;
struct TYPE_4__ {char* name; } ;

/* Variables and functions */
 scalar_t__ RCB_IRQ_INITED ; 
 int RCB_RING_NAME_LEN ; 
 scalar_t__ cpu_online (int) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_irq_handle ; 
 int /*<<< orphan*/  hns_nic_free_irq (int,struct hns_nic_priv*) ; 
 int hns_nic_init_affinity_mask (int,int,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_set_affinity_hint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ is_tx_ring (TYPE_2__*) ; 
 int /*<<< orphan*/  netdev_err (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct hns_nic_ring_data*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hns_nic_init_irq(struct hns_nic_priv *priv)
{
	struct hnae_handle *h = priv->ae_handle;
	struct hns_nic_ring_data *rd;
	int i;
	int ret;
	int cpu;

	for (i = 0; i < h->q_num * 2; i++) {
		rd = &priv->ring_data[i];

		if (rd->ring->irq_init_flag == RCB_IRQ_INITED)
			break;

		snprintf(rd->ring->ring_name, RCB_RING_NAME_LEN,
			 "%s-%s%d", priv->netdev->name,
			 (is_tx_ring(rd->ring) ? "tx" : "rx"), rd->queue_index);

		rd->ring->ring_name[RCB_RING_NAME_LEN - 1] = '\0';

		ret = request_irq(rd->ring->irq,
				  hns_irq_handle, 0, rd->ring->ring_name, rd);
		if (ret) {
			netdev_err(priv->netdev, "request irq(%d) fail\n",
				   rd->ring->irq);
			goto out_free_irq;
		}
		disable_irq(rd->ring->irq);

		cpu = hns_nic_init_affinity_mask(h->q_num, i,
						 rd->ring, &rd->mask);

		if (cpu_online(cpu))
			irq_set_affinity_hint(rd->ring->irq,
					      &rd->mask);

		rd->ring->irq_init_flag = RCB_IRQ_INITED;
	}

	return 0;

out_free_irq:
	hns_nic_free_irq(h->q_num, priv);
	return ret;
}