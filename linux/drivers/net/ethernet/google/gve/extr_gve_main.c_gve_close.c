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
struct net_device {int dummy; } ;
struct gve_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gve_clear_device_rings_ok (struct gve_priv*) ; 
 int gve_destroy_rings (struct gve_priv*) ; 
 int /*<<< orphan*/  gve_free_qpls (struct gve_priv*) ; 
 int /*<<< orphan*/  gve_free_rings (struct gve_priv*) ; 
 scalar_t__ gve_get_device_rings_ok (struct gve_priv*) ; 
 scalar_t__ gve_get_reset_in_progress (struct gve_priv*) ; 
 int /*<<< orphan*/  gve_reset_and_teardown (struct gve_priv*,int) ; 
 int gve_reset_recovery (struct gve_priv*,int) ; 
 int /*<<< orphan*/  gve_turndown (struct gve_priv*) ; 
 int gve_unregister_qpls (struct gve_priv*) ; 
 struct gve_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 

__attribute__((used)) static int gve_close(struct net_device *dev)
{
	struct gve_priv *priv = netdev_priv(dev);
	int err;

	netif_carrier_off(dev);
	if (gve_get_device_rings_ok(priv)) {
		gve_turndown(priv);
		err = gve_destroy_rings(priv);
		if (err)
			goto err;
		err = gve_unregister_qpls(priv);
		if (err)
			goto err;
		gve_clear_device_rings_ok(priv);
	}

	gve_free_rings(priv);
	gve_free_qpls(priv);
	return 0;

err:
	/* This must have been called from a reset due to the rtnl lock
	 * so just return at this point.
	 */
	if (gve_get_reset_in_progress(priv))
		return err;
	/* Otherwise reset before returning */
	gve_reset_and_teardown(priv, true);
	return gve_reset_recovery(priv, false);
}