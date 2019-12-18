#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int num_queues; } ;
struct gve_priv {int /*<<< orphan*/  dev; TYPE_1__ tx_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  drv ; 
 int gve_tx_alloc_ring (struct gve_priv*,int) ; 
 int /*<<< orphan*/  gve_tx_free_ring (struct gve_priv*,int) ; 
 int /*<<< orphan*/  netif_err (struct gve_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 

int gve_tx_alloc_rings(struct gve_priv *priv)
{
	int err = 0;
	int i;

	for (i = 0; i < priv->tx_cfg.num_queues; i++) {
		err = gve_tx_alloc_ring(priv, i);
		if (err) {
			netif_err(priv, drv, priv->dev,
				  "Failed to alloc tx ring=%d: err=%d\n",
				  i, err);
			break;
		}
	}
	/* Unallocate if there was an error */
	if (err) {
		int j;

		for (j = 0; j < i; j++)
			gve_tx_free_ring(priv, j);
	}
	return err;
}