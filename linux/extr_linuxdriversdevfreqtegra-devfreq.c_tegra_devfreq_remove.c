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
typedef  int /*<<< orphan*/  u32 ;
struct tegra_devfreq {int /*<<< orphan*/  clock; int /*<<< orphan*/  rate_change_nb; int /*<<< orphan*/  emc_clock; int /*<<< orphan*/ * devices; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACTMON_DEV_CTRL ; 
 int /*<<< orphan*/  ACTMON_DEV_CTRL_ENB ; 
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  actmon_device_configs ; 
 int /*<<< orphan*/  actmon_write_barrier (struct tegra_devfreq*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_notifier_unregister (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_readl (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_writel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_free_irq (int /*<<< orphan*/ *,int,struct tegra_devfreq*) ; 
 struct tegra_devfreq* platform_get_drvdata (struct platform_device*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_devfreq_remove(struct platform_device *pdev)
{
	struct tegra_devfreq *tegra = platform_get_drvdata(pdev);
	int irq = platform_get_irq(pdev, 0);
	u32 val;
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(actmon_device_configs); i++) {
		val = device_readl(&tegra->devices[i], ACTMON_DEV_CTRL);
		val &= ~ACTMON_DEV_CTRL_ENB;
		device_writel(&tegra->devices[i], val, ACTMON_DEV_CTRL);
	}

	actmon_write_barrier(tegra);

	devm_free_irq(&pdev->dev, irq, tegra);

	clk_notifier_unregister(tegra->emc_clock, &tegra->rate_change_nb);

	clk_disable_unprepare(tegra->clock);

	return 0;
}