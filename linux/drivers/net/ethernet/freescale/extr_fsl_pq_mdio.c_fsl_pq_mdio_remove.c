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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct mii_bus {struct fsl_pq_mdio_priv* priv; } ;
struct fsl_pq_mdio_priv {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 struct mii_bus* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdiobus_free (struct mii_bus*) ; 
 int /*<<< orphan*/  mdiobus_unregister (struct mii_bus*) ; 

__attribute__((used)) static int fsl_pq_mdio_remove(struct platform_device *pdev)
{
	struct device *device = &pdev->dev;
	struct mii_bus *bus = dev_get_drvdata(device);
	struct fsl_pq_mdio_priv *priv = bus->priv;

	mdiobus_unregister(bus);

	iounmap(priv->map);
	mdiobus_free(bus);

	return 0;
}