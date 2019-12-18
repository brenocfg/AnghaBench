#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct gve_tx_ring {int ntfy_id; } ;
struct gve_priv {struct gve_tx_ring* tx; struct gve_notify_block* ntfy_blocks; } ;
struct gve_notify_block {struct gve_tx_ring* tx; } ;

/* Variables and functions */
 int gve_tx_idx_to_ntfy (struct gve_priv*,int) ; 

__attribute__((used)) static void gve_tx_add_to_block(struct gve_priv *priv, int queue_idx)
{
	int ntfy_idx = gve_tx_idx_to_ntfy(priv, queue_idx);
	struct gve_notify_block *block = &priv->ntfy_blocks[ntfy_idx];
	struct gve_tx_ring *tx = &priv->tx[queue_idx];

	block->tx = tx;
	tx->ntfy_id = ntfy_idx;
}