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
struct omap_i2c_dev {int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP_I2C_CON_REG ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap_i2c_write_reg (struct omap_i2c_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct omap_i2c_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_dont_use_autosuspend (int /*<<< orphan*/ *) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int omap_i2c_remove(struct platform_device *pdev)
{
	struct omap_i2c_dev	*omap = platform_get_drvdata(pdev);
	int ret;

	i2c_del_adapter(&omap->adapter);
	ret = pm_runtime_get_sync(&pdev->dev);
	if (ret < 0)
		return ret;

	omap_i2c_write_reg(omap, OMAP_I2C_CON_REG, 0);
	pm_runtime_dont_use_autosuspend(&pdev->dev);
	pm_runtime_put_sync(&pdev->dev);
	pm_runtime_disable(&pdev->dev);
	return 0;
}