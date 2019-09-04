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
struct tegra_dfll {int /*<<< orphan*/  ref_clk; int /*<<< orphan*/  soc_clk; int /*<<< orphan*/  i2c_clk; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct tegra_dfll* dev_get_drvdata (struct device*) ; 

int tegra_dfll_runtime_resume(struct device *dev)
{
	struct tegra_dfll *td = dev_get_drvdata(dev);
	int ret;

	ret = clk_enable(td->ref_clk);
	if (ret) {
		dev_err(dev, "could not enable ref clock: %d\n", ret);
		return ret;
	}

	ret = clk_enable(td->soc_clk);
	if (ret) {
		dev_err(dev, "could not enable register clock: %d\n", ret);
		clk_disable(td->ref_clk);
		return ret;
	}

	ret = clk_enable(td->i2c_clk);
	if (ret) {
		dev_err(dev, "could not enable i2c clock: %d\n", ret);
		clk_disable(td->soc_clk);
		clk_disable(td->ref_clk);
		return ret;
	}

	return 0;
}