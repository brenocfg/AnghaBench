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
struct rcar_gen3_thermal_priv {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 struct rcar_gen3_thermal_priv* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put (struct device*) ; 
 int /*<<< orphan*/  rcar_thermal_irq_set (struct rcar_gen3_thermal_priv*,int) ; 

__attribute__((used)) static int rcar_gen3_thermal_remove(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct rcar_gen3_thermal_priv *priv = dev_get_drvdata(dev);

	rcar_thermal_irq_set(priv, false);

	pm_runtime_put(dev);
	pm_runtime_disable(dev);

	return 0;
}