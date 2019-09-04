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
struct tegra_i2c_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  fast_clk; TYPE_1__* hw; int /*<<< orphan*/  div_clk; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  has_single_clk_source; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 struct tegra_i2c_dev* dev_get_drvdata (struct device*) ; 
 int pinctrl_pm_select_idle_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_i2c_runtime_suspend(struct device *dev)
{
	struct tegra_i2c_dev *i2c_dev = dev_get_drvdata(dev);

	clk_disable(i2c_dev->div_clk);
	if (!i2c_dev->hw->has_single_clk_source)
		clk_disable(i2c_dev->fast_clk);

	return pinctrl_pm_select_idle_state(i2c_dev->dev);
}