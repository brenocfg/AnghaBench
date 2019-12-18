#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct gswip_priv {int num_gphy_fw; int /*<<< orphan*/ * gphy_fw; TYPE_3__* ds; } ;
struct TYPE_6__ {TYPE_2__* slave_mii_bus; } ;
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_5__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GSWIP_MDIO_GLOB ; 
 int /*<<< orphan*/  GSWIP_MDIO_GLOB_ENABLE ; 
 int /*<<< orphan*/  dsa_unregister_switch (TYPE_3__*) ; 
 int /*<<< orphan*/  gswip_gphy_fw_remove (struct gswip_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gswip_mdio_mask (struct gswip_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdiobus_unregister (TYPE_2__*) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 struct gswip_priv* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int gswip_remove(struct platform_device *pdev)
{
	struct gswip_priv *priv = platform_get_drvdata(pdev);
	int i;

	/* disable the switch */
	gswip_mdio_mask(priv, GSWIP_MDIO_GLOB_ENABLE, 0, GSWIP_MDIO_GLOB);

	dsa_unregister_switch(priv->ds);

	if (priv->ds->slave_mii_bus) {
		mdiobus_unregister(priv->ds->slave_mii_bus);
		of_node_put(priv->ds->slave_mii_bus->dev.of_node);
	}

	for (i = 0; i < priv->num_gphy_fw; i++)
		gswip_gphy_fw_remove(priv, &priv->gphy_fw[i]);

	return 0;
}