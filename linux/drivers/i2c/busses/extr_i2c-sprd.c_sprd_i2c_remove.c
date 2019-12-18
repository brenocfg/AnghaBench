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
struct sprd_i2c {int /*<<< orphan*/  dev; int /*<<< orphan*/  clk; int /*<<< orphan*/  adap; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 struct sprd_i2c* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sprd_i2c_remove(struct platform_device *pdev)
{
	struct sprd_i2c *i2c_dev = platform_get_drvdata(pdev);
	int ret;

	ret = pm_runtime_get_sync(i2c_dev->dev);
	if (ret < 0)
		return ret;

	i2c_del_adapter(&i2c_dev->adap);
	clk_disable_unprepare(i2c_dev->clk);

	pm_runtime_put_noidle(i2c_dev->dev);
	pm_runtime_disable(i2c_dev->dev);

	return 0;
}