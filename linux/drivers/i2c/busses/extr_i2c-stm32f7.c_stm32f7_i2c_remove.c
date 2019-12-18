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
struct stm32f7_i2c_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  clk; int /*<<< orphan*/  adap; int /*<<< orphan*/ * dma; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 struct stm32f7_i2c_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_dont_use_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32_i2c_dma_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int stm32f7_i2c_remove(struct platform_device *pdev)
{
	struct stm32f7_i2c_dev *i2c_dev = platform_get_drvdata(pdev);

	if (i2c_dev->dma) {
		stm32_i2c_dma_free(i2c_dev->dma);
		i2c_dev->dma = NULL;
	}

	i2c_del_adapter(&i2c_dev->adap);
	pm_runtime_get_sync(i2c_dev->dev);

	clk_disable_unprepare(i2c_dev->clk);

	pm_runtime_put_noidle(i2c_dev->dev);
	pm_runtime_disable(i2c_dev->dev);
	pm_runtime_set_suspended(i2c_dev->dev);
	pm_runtime_dont_use_autosuspend(i2c_dev->dev);

	return 0;
}