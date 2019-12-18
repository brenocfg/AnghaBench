#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int num_queues; } ;
struct TYPE_4__ {int num_queues; } ;
struct gve_priv {TYPE_3__* tx; TYPE_3__* rx; TYPE_2__ rx_cfg; TYPE_1__ tx_cfg; } ;
struct TYPE_6__ {int /*<<< orphan*/  statss; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  gve_add_napi (struct gve_priv*,int) ; 
 int gve_rx_alloc_rings (struct gve_priv*) ; 
 int gve_rx_idx_to_ntfy (struct gve_priv*,int) ; 
 int gve_tx_alloc_rings (struct gve_priv*) ; 
 int /*<<< orphan*/  gve_tx_free_rings (struct gve_priv*) ; 
 int gve_tx_idx_to_ntfy (struct gve_priv*,int) ; 
 int /*<<< orphan*/  kvfree (TYPE_3__*) ; 
 void* kvzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64_stats_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gve_alloc_rings(struct gve_priv *priv)
{
	int ntfy_idx;
	int err;
	int i;

	/* Setup tx rings */
	priv->tx = kvzalloc(priv->tx_cfg.num_queues * sizeof(*priv->tx),
			    GFP_KERNEL);
	if (!priv->tx)
		return -ENOMEM;
	err = gve_tx_alloc_rings(priv);
	if (err)
		goto free_tx;
	/* Setup rx rings */
	priv->rx = kvzalloc(priv->rx_cfg.num_queues * sizeof(*priv->rx),
			    GFP_KERNEL);
	if (!priv->rx) {
		err = -ENOMEM;
		goto free_tx_queue;
	}
	err = gve_rx_alloc_rings(priv);
	if (err)
		goto free_rx;
	/* Add tx napi & init sync stats*/
	for (i = 0; i < priv->tx_cfg.num_queues; i++) {
		u64_stats_init(&priv->tx[i].statss);
		ntfy_idx = gve_tx_idx_to_ntfy(priv, i);
		gve_add_napi(priv, ntfy_idx);
	}
	/* Add rx napi  & init sync stats*/
	for (i = 0; i < priv->rx_cfg.num_queues; i++) {
		u64_stats_init(&priv->rx[i].statss);
		ntfy_idx = gve_rx_idx_to_ntfy(priv, i);
		gve_add_napi(priv, ntfy_idx);
	}

	return 0;

free_rx:
	kvfree(priv->rx);
	priv->rx = NULL;
free_tx_queue:
	gve_tx_free_rings(priv);
free_tx:
	kvfree(priv->tx);
	priv->tx = NULL;
	return err;
}