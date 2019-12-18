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
struct net_device {int /*<<< orphan*/  phydev; } ;
struct gfar_private {int /*<<< orphan*/  reset_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfar_free_irq (struct gfar_private*) ; 
 struct gfar_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stop_gfar (struct net_device*) ; 

__attribute__((used)) static int gfar_close(struct net_device *dev)
{
	struct gfar_private *priv = netdev_priv(dev);

	cancel_work_sync(&priv->reset_task);
	stop_gfar(dev);

	/* Disconnect from the PHY */
	phy_disconnect(dev->phydev);

	gfar_free_irq(priv);

	return 0;
}