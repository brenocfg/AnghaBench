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
struct tegra_dfll_soc_data {int dummy; } ;
struct tegra_dfll {scalar_t__ mode; struct tegra_dfll_soc_data* soc; int /*<<< orphan*/  dvco_rst; int /*<<< orphan*/  i2c_clk; int /*<<< orphan*/  soc_clk; int /*<<< orphan*/  ref_clk; int /*<<< orphan*/  debugfs_dir; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ DFLL_DISABLED ; 
 int /*<<< orphan*/  EBUSY ; 
 struct tegra_dfll_soc_data* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dfll_unregister_clk (struct tegra_dfll*) ; 
 struct tegra_dfll* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 

struct tegra_dfll_soc_data *tegra_dfll_unregister(struct platform_device *pdev)
{
	struct tegra_dfll *td = platform_get_drvdata(pdev);

	/* Try to prevent removal while the DFLL is active */
	if (td->mode != DFLL_DISABLED) {
		dev_err(&pdev->dev,
			"must disable DFLL before removing driver\n");
		return ERR_PTR(-EBUSY);
	}

	debugfs_remove_recursive(td->debugfs_dir);

	dfll_unregister_clk(td);
	pm_runtime_disable(&pdev->dev);

	clk_unprepare(td->ref_clk);
	clk_unprepare(td->soc_clk);
	clk_unprepare(td->i2c_clk);

	reset_control_assert(td->dvco_rst);

	return td->soc;
}