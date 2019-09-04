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
struct tegra_adma {int /*<<< orphan*/  global_cmd; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADMA_GLOBAL_CMD ; 
 struct tegra_adma* dev_get_drvdata (struct device*) ; 
 int pm_clk_suspend (struct device*) ; 
 int /*<<< orphan*/  tdma_read (struct tegra_adma*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_adma_runtime_suspend(struct device *dev)
{
	struct tegra_adma *tdma = dev_get_drvdata(dev);

	tdma->global_cmd = tdma_read(tdma, ADMA_GLOBAL_CMD);

	return pm_clk_suspend(dev);
}