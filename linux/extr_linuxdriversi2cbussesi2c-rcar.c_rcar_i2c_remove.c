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
struct rcar_i2c_priv {int flags; int /*<<< orphan*/  adap; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int ID_P_PM_BLOCKED ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 struct rcar_i2c_priv* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put (struct device*) ; 
 int /*<<< orphan*/  rcar_i2c_release_dma (struct rcar_i2c_priv*) ; 

__attribute__((used)) static int rcar_i2c_remove(struct platform_device *pdev)
{
	struct rcar_i2c_priv *priv = platform_get_drvdata(pdev);
	struct device *dev = &pdev->dev;

	i2c_del_adapter(&priv->adap);
	rcar_i2c_release_dma(priv);
	if (priv->flags & ID_P_PM_BLOCKED)
		pm_runtime_put(dev);
	pm_runtime_disable(dev);

	return 0;
}