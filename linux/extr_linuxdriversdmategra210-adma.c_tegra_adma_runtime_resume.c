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
 int pm_clk_resume (struct device*) ; 
 int /*<<< orphan*/  tdma_write (struct tegra_adma*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_adma_runtime_resume(struct device *dev)
{
	struct tegra_adma *tdma = dev_get_drvdata(dev);
	int ret;

	ret = pm_clk_resume(dev);
	if (ret)
		return ret;

	tdma_write(tdma, ADMA_GLOBAL_CMD, tdma->global_cmd);

	return 0;
}