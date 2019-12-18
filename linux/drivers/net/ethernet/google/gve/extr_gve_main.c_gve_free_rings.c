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
struct TYPE_3__ {int num_queues; } ;
struct TYPE_4__ {int num_queues; } ;
struct gve_priv {int /*<<< orphan*/ * rx; TYPE_1__ rx_cfg; int /*<<< orphan*/ * tx; TYPE_2__ tx_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  gve_remove_napi (struct gve_priv*,int) ; 
 int /*<<< orphan*/  gve_rx_free_rings (struct gve_priv*) ; 
 int gve_rx_idx_to_ntfy (struct gve_priv*,int) ; 
 int /*<<< orphan*/  gve_tx_free_rings (struct gve_priv*) ; 
 int gve_tx_idx_to_ntfy (struct gve_priv*,int) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gve_free_rings(struct gve_priv *priv)
{
	int ntfy_idx;
	int i;

	if (priv->tx) {
		for (i = 0; i < priv->tx_cfg.num_queues; i++) {
			ntfy_idx = gve_tx_idx_to_ntfy(priv, i);
			gve_remove_napi(priv, ntfy_idx);
		}
		gve_tx_free_rings(priv);
		kvfree(priv->tx);
		priv->tx = NULL;
	}
	if (priv->rx) {
		for (i = 0; i < priv->rx_cfg.num_queues; i++) {
			ntfy_idx = gve_rx_idx_to_ntfy(priv, i);
			gve_remove_napi(priv, ntfy_idx);
		}
		gve_rx_free_rings(priv);
		kvfree(priv->rx);
		priv->rx = NULL;
	}
}