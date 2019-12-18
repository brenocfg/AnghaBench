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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct mlxreg_hotplug_priv_data {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 struct mlxreg_hotplug_priv_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_free_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mlxreg_hotplug_priv_data*) ; 
 int /*<<< orphan*/  mlxreg_hotplug_unset_irq (struct mlxreg_hotplug_priv_data*) ; 

__attribute__((used)) static int mlxreg_hotplug_remove(struct platform_device *pdev)
{
	struct mlxreg_hotplug_priv_data *priv = dev_get_drvdata(&pdev->dev);

	/* Clean interrupts setup. */
	mlxreg_hotplug_unset_irq(priv);
	devm_free_irq(&pdev->dev, priv->irq, priv);

	return 0;
}