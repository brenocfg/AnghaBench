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
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  num_queues; } ;
struct TYPE_3__ {int /*<<< orphan*/  num_queues; } ;
struct gve_priv {TYPE_2__ rx_cfg; TYPE_1__ tx_cfg; } ;

/* Variables and functions */
 int gve_alloc_qpls (struct gve_priv*) ; 
 int gve_alloc_rings (struct gve_priv*) ; 
 int gve_create_rings (struct gve_priv*) ; 
 int /*<<< orphan*/  gve_free_qpls (struct gve_priv*) ; 
 int /*<<< orphan*/  gve_free_rings (struct gve_priv*) ; 
 scalar_t__ gve_get_reset_in_progress (struct gve_priv*) ; 
 int gve_register_qpls (struct gve_priv*) ; 
 int /*<<< orphan*/  gve_reset_and_teardown (struct gve_priv*,int) ; 
 int /*<<< orphan*/  gve_reset_recovery (struct gve_priv*,int) ; 
 int /*<<< orphan*/  gve_set_device_rings_ok (struct gve_priv*) ; 
 int /*<<< orphan*/  gve_turnup (struct gve_priv*) ; 
 struct gve_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int netif_set_real_num_rx_queues (struct net_device*,int /*<<< orphan*/ ) ; 
 int netif_set_real_num_tx_queues (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gve_open(struct net_device *dev)
{
	struct gve_priv *priv = netdev_priv(dev);
	int err;

	err = gve_alloc_qpls(priv);
	if (err)
		return err;
	err = gve_alloc_rings(priv);
	if (err)
		goto free_qpls;

	err = netif_set_real_num_tx_queues(dev, priv->tx_cfg.num_queues);
	if (err)
		goto free_rings;
	err = netif_set_real_num_rx_queues(dev, priv->rx_cfg.num_queues);
	if (err)
		goto free_rings;

	err = gve_register_qpls(priv);
	if (err)
		goto reset;
	err = gve_create_rings(priv);
	if (err)
		goto reset;
	gve_set_device_rings_ok(priv);

	gve_turnup(priv);
	netif_carrier_on(dev);
	return 0;

free_rings:
	gve_free_rings(priv);
free_qpls:
	gve_free_qpls(priv);
	return err;

reset:
	/* This must have been called from a reset due to the rtnl lock
	 * so just return at this point.
	 */
	if (gve_get_reset_in_progress(priv))
		return err;
	/* Otherwise reset before returning */
	gve_reset_and_teardown(priv, true);
	/* if this fails there is nothing we can do so just ignore the return */
	gve_reset_recovery(priv, false);
	/* return the original error */
	return err;
}