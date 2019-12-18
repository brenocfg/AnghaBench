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
struct TYPE_4__ {int num_queues; } ;
struct TYPE_3__ {int num_queues; } ;
struct gve_priv {struct gve_notify_block* ntfy_blocks; TYPE_2__ rx_cfg; TYPE_1__ tx_cfg; int /*<<< orphan*/  dev; } ;
struct gve_notify_block {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  gve_irq_doorbell (struct gve_priv*,struct gve_notify_block*) ; 
 int gve_rx_idx_to_ntfy (struct gve_priv*,int) ; 
 int /*<<< orphan*/  gve_set_napi_enabled (struct gve_priv*) ; 
 int gve_tx_idx_to_ntfy (struct gve_priv*,int) ; 
 int /*<<< orphan*/  iowrite32be (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_tx_start_all_queues (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gve_turnup(struct gve_priv *priv)
{
	int idx;

	/* Start the tx queues */
	netif_tx_start_all_queues(priv->dev);

	/* Enable napi and unmask interrupts for all queues */
	for (idx = 0; idx < priv->tx_cfg.num_queues; idx++) {
		int ntfy_idx = gve_tx_idx_to_ntfy(priv, idx);
		struct gve_notify_block *block = &priv->ntfy_blocks[ntfy_idx];

		napi_enable(&block->napi);
		iowrite32be(0, gve_irq_doorbell(priv, block));
	}
	for (idx = 0; idx < priv->rx_cfg.num_queues; idx++) {
		int ntfy_idx = gve_rx_idx_to_ntfy(priv, idx);
		struct gve_notify_block *block = &priv->ntfy_blocks[ntfy_idx];

		napi_enable(&block->napi);
		iowrite32be(0, gve_irq_doorbell(priv, block));
	}

	gve_set_napi_enabled(priv);
}