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
struct unimac_mdio_priv {int /*<<< orphan*/  clk; int /*<<< orphan*/  mii_bus; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdiobus_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdiobus_unregister (int /*<<< orphan*/ ) ; 
 struct unimac_mdio_priv* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int unimac_mdio_remove(struct platform_device *pdev)
{
	struct unimac_mdio_priv *priv = platform_get_drvdata(pdev);

	mdiobus_unregister(priv->mii_bus);
	mdiobus_free(priv->mii_bus);
	clk_disable_unprepare(priv->clk);

	return 0;
}