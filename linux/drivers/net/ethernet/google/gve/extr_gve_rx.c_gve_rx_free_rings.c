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
struct gve_priv {TYPE_1__ rx_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  gve_rx_free_ring (struct gve_priv*,int) ; 

void gve_rx_free_rings(struct gve_priv *priv)
{
	int i;

	for (i = 0; i < priv->rx_cfg.num_queues; i++)
		gve_rx_free_ring(priv, i);
}