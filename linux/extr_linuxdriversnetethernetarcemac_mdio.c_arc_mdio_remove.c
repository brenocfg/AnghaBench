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
struct arc_emac_priv {int /*<<< orphan*/ * bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  mdiobus_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mdiobus_unregister (int /*<<< orphan*/ *) ; 

int arc_mdio_remove(struct arc_emac_priv *priv)
{
	mdiobus_unregister(priv->bus);
	mdiobus_free(priv->bus);
	priv->bus = NULL;

	return 0;
}