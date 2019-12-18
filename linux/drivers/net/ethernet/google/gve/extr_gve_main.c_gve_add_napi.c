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
struct gve_priv {int /*<<< orphan*/  dev; struct gve_notify_block* ntfy_blocks; } ;
struct gve_notify_block {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAPI_POLL_WEIGHT ; 
 int /*<<< orphan*/  gve_napi_poll ; 
 int /*<<< orphan*/  netif_napi_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gve_add_napi(struct gve_priv *priv, int ntfy_idx)
{
	struct gve_notify_block *block = &priv->ntfy_blocks[ntfy_idx];

	netif_napi_add(priv->dev, &block->napi, gve_napi_poll,
		       NAPI_POLL_WEIGHT);
}