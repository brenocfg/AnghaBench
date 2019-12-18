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
struct net_device {scalar_t__ reg_state; } ;
struct lbs_private {struct net_device* dev; } ;

/* Variables and functions */
 scalar_t__ NETREG_REGISTERED ; 
 int /*<<< orphan*/  lbs_debugfs_remove_one (struct lbs_private*) ; 
 int /*<<< orphan*/  lbs_deinit_mesh (struct lbs_private*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

void lbs_stop_card(struct lbs_private *priv)
{
	struct net_device *dev;

	if (!priv)
		return;
	dev = priv->dev;

	/* If the netdev isn't registered, it means that lbs_start_card() was
	 * never called so we have nothing to do here. */
	if (dev->reg_state != NETREG_REGISTERED)
		return;

	netif_stop_queue(dev);
	netif_carrier_off(dev);

	lbs_debugfs_remove_one(priv);
	lbs_deinit_mesh(priv);
	unregister_netdev(dev);
}