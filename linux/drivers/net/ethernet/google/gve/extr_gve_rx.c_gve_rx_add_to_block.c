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
typedef  size_t u32 ;
struct gve_rx_ring {size_t ntfy_id; } ;
struct gve_priv {struct gve_rx_ring* rx; struct gve_notify_block* ntfy_blocks; } ;
struct gve_notify_block {struct gve_rx_ring* rx; } ;

/* Variables and functions */
 size_t gve_rx_idx_to_ntfy (struct gve_priv*,int) ; 

__attribute__((used)) static void gve_rx_add_to_block(struct gve_priv *priv, int queue_idx)
{
	u32 ntfy_idx = gve_rx_idx_to_ntfy(priv, queue_idx);
	struct gve_notify_block *block = &priv->ntfy_blocks[ntfy_idx];
	struct gve_rx_ring *rx = &priv->rx[queue_idx];

	block->rx = rx;
	rx->ntfy_id = ntfy_idx;
}