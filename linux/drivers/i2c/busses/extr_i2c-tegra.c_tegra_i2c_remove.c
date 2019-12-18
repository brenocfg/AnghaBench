#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tegra_i2c_dev {int /*<<< orphan*/  fast_clk; TYPE_1__* hw; int /*<<< orphan*/  div_clk; scalar_t__ is_multimaster_mode; int /*<<< orphan*/  adapter; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  has_single_clk_source; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 struct tegra_i2c_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_status_suspended (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tegra_i2c_release_dma (struct tegra_i2c_dev*) ; 
 int /*<<< orphan*/  tegra_i2c_runtime_suspend (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tegra_i2c_remove(struct platform_device *pdev)
{
	struct tegra_i2c_dev *i2c_dev = platform_get_drvdata(pdev);

	i2c_del_adapter(&i2c_dev->adapter);

	if (i2c_dev->is_multimaster_mode)
		clk_disable(i2c_dev->div_clk);

	pm_runtime_disable(&pdev->dev);
	if (!pm_runtime_status_suspended(&pdev->dev))
		tegra_i2c_runtime_suspend(&pdev->dev);

	clk_unprepare(i2c_dev->div_clk);
	if (!i2c_dev->hw->has_single_clk_source)
		clk_unprepare(i2c_dev->fast_clk);

	tegra_i2c_release_dma(i2c_dev);
	return 0;
}