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
struct gve_priv {int /*<<< orphan*/  dev; TYPE_1__ rx_cfg; TYPE_2__ tx_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  drv ; 
 int gve_adminq_destroy_rx_queue (struct gve_priv*,int) ; 
 int gve_adminq_destroy_tx_queue (struct gve_priv*,int) ; 
 int /*<<< orphan*/  netif_dbg (struct gve_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  netif_err (struct gve_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int gve_destroy_rings(struct gve_priv *priv)
{
	int err;
	int i;

	for (i = 0; i < priv->tx_cfg.num_queues; i++) {
		err = gve_adminq_destroy_tx_queue(priv, i);
		if (err) {
			netif_err(priv, drv, priv->dev,
				  "failed to destroy tx queue %d\n",
				  i);
			/* This failure will trigger a reset - no need to clean
			 * up
			 */
			return err;
		}
		netif_dbg(priv, drv, priv->dev, "destroyed tx queue %d\n", i);
	}
	for (i = 0; i < priv->rx_cfg.num_queues; i++) {
		err = gve_adminq_destroy_rx_queue(priv, i);
		if (err) {
			netif_err(priv, drv, priv->dev,
				  "failed to destroy rx queue %d\n",
				  i);
			/* This failure will trigger a reset - no need to clean
			 * up
			 */
			return err;
		}
		netif_dbg(priv, drv, priv->dev, "destroyed rx queue %d\n", i);
	}
	return 0;
}