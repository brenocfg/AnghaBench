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
struct TYPE_2__ {int /*<<< orphan*/  qpl_id_map; } ;
struct gve_priv {int /*<<< orphan*/  qpls; TYPE_1__ qpl_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  gve_free_queue_page_list (struct gve_priv*,int) ; 
 int gve_num_rx_qpls (struct gve_priv*) ; 
 int gve_num_tx_qpls (struct gve_priv*) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gve_free_qpls(struct gve_priv *priv)
{
	int num_qpls = gve_num_tx_qpls(priv) + gve_num_rx_qpls(priv);
	int i;

	kvfree(priv->qpl_cfg.qpl_id_map);

	for (i = 0; i < num_qpls; i++)
		gve_free_queue_page_list(priv, i);

	kvfree(priv->qpls);
}