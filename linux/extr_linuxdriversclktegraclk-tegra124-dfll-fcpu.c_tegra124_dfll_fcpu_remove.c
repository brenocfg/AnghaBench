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
struct tegra_dfll_soc_data {int /*<<< orphan*/  max_freq; int /*<<< orphan*/  cvb; int /*<<< orphan*/  dev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct tegra_dfll_soc_data*) ; 
 int PTR_ERR (struct tegra_dfll_soc_data*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  tegra_cvb_remove_opp_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tegra_dfll_soc_data* tegra_dfll_unregister (struct platform_device*) ; 

__attribute__((used)) static int tegra124_dfll_fcpu_remove(struct platform_device *pdev)
{
	struct tegra_dfll_soc_data *soc;

	soc = tegra_dfll_unregister(pdev);
	if (IS_ERR(soc)) {
		dev_err(&pdev->dev, "failed to unregister DFLL: %ld\n",
			PTR_ERR(soc));
		return PTR_ERR(soc);
	}

	tegra_cvb_remove_opp_table(soc->dev, soc->cvb, soc->max_freq);

	return 0;
}