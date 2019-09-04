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
struct tegra_dfll {int /*<<< orphan*/  i2c_clk; int /*<<< orphan*/  soc_clk; int /*<<< orphan*/  ref_clk; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 struct tegra_dfll* dev_get_drvdata (struct device*) ; 

int tegra_dfll_runtime_suspend(struct device *dev)
{
	struct tegra_dfll *td = dev_get_drvdata(dev);

	clk_disable(td->ref_clk);
	clk_disable(td->soc_clk);
	clk_disable(td->i2c_clk);

	return 0;
}