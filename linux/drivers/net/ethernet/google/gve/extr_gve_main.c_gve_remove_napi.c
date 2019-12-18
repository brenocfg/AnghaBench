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
struct gve_priv {struct gve_notify_block* ntfy_blocks; } ;
struct gve_notify_block {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gve_remove_napi(struct gve_priv *priv, int ntfy_idx)
{
	struct gve_notify_block *block = &priv->ntfy_blocks[ntfy_idx];

	netif_napi_del(&block->napi);
}