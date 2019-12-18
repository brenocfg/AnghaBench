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
struct platform_device {int dummy; } ;
struct at91_twi_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  clk; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 struct at91_twi_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int at91_twi_remove(struct platform_device *pdev)
{
	struct at91_twi_dev *dev = platform_get_drvdata(pdev);

	i2c_del_adapter(&dev->adapter);
	clk_disable_unprepare(dev->clk);

	pm_runtime_disable(dev->dev);
	pm_runtime_set_suspended(dev->dev);

	return 0;
}