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
struct gve_priv {TYPE_1__* qpls; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  drv ; 
 int gve_adminq_register_page_list (struct gve_priv*,TYPE_1__*) ; 
 int gve_num_rx_qpls (struct gve_priv*) ; 
 int gve_num_tx_qpls (struct gve_priv*) ; 
 int /*<<< orphan*/  netif_err (struct gve_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gve_register_qpls(struct gve_priv *priv)
{
	int num_qpls = gve_num_tx_qpls(priv) + gve_num_rx_qpls(priv);
	int err;
	int i;

	for (i = 0; i < num_qpls; i++) {
		err = gve_adminq_register_page_list(priv, &priv->qpls[i]);
		if (err) {
			netif_err(priv, drv, priv->dev,
				  "failed to register queue page list %d\n",
				  priv->qpls[i].id);
			/* This failure will trigger a reset - no need to clean
			 * up
			 */
			return err;
		}
	}
	return 0;
}