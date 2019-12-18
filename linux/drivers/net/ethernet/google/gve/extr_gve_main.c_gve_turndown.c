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
struct gve_priv {int /*<<< orphan*/  dev; struct gve_notify_block* ntfy_blocks; TYPE_2__ rx_cfg; TYPE_1__ tx_cfg; } ;
struct gve_notify_block {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  gve_clear_napi_enabled (struct gve_priv*) ; 
 int /*<<< orphan*/  gve_get_napi_enabled (struct gve_priv*) ; 
 int gve_rx_idx_to_ntfy (struct gve_priv*,int) ; 
 int gve_tx_idx_to_ntfy (struct gve_priv*,int) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 scalar_t__ netif_carrier_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gve_turndown(struct gve_priv *priv)
{
	int idx;

	if (netif_carrier_ok(priv->dev))
		netif_carrier_off(priv->dev);

	if (!gve_get_napi_enabled(priv))
		return;

	/* Disable napi to prevent more work from coming in */
	for (idx = 0; idx < priv->tx_cfg.num_queues; idx++) {
		int ntfy_idx = gve_tx_idx_to_ntfy(priv, idx);
		struct gve_notify_block *block = &priv->ntfy_blocks[ntfy_idx];

		napi_disable(&block->napi);
	}
	for (idx = 0; idx < priv->rx_cfg.num_queues; idx++) {
		int ntfy_idx = gve_rx_idx_to_ntfy(priv, idx);
		struct gve_notify_block *block = &priv->ntfy_blocks[ntfy_idx];

		napi_disable(&block->napi);
	}

	/* Stop tx queues */
	netif_tx_disable(priv->dev);

	gve_clear_napi_enabled(priv);
}