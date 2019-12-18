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
struct bcm_sf2_priv {int /*<<< orphan*/  master_mii_dn; int /*<<< orphan*/  slave_mii_bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  mdiobus_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm_sf2_mdio_unregister(struct bcm_sf2_priv *priv)
{
	mdiobus_unregister(priv->slave_mii_bus);
	of_node_put(priv->master_mii_dn);
}