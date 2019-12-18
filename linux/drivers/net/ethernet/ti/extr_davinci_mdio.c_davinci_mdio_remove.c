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
struct davinci_mdio_data {scalar_t__ bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  mdiobus_unregister (scalar_t__) ; 
 struct davinci_mdio_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_dont_use_autosuspend (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int davinci_mdio_remove(struct platform_device *pdev)
{
	struct davinci_mdio_data *data = platform_get_drvdata(pdev);

	if (data->bus)
		mdiobus_unregister(data->bus);

	pm_runtime_dont_use_autosuspend(&pdev->dev);
	pm_runtime_disable(&pdev->dev);

	return 0;
}