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
struct tegra_dc {int /*<<< orphan*/  client; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int host1x_client_unregister (int /*<<< orphan*/ *) ; 
 struct tegra_dc* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int tegra_dc_rgb_remove (struct tegra_dc*) ; 

__attribute__((used)) static int tegra_dc_remove(struct platform_device *pdev)
{
	struct tegra_dc *dc = platform_get_drvdata(pdev);
	int err;

	err = host1x_client_unregister(&dc->client);
	if (err < 0) {
		dev_err(&pdev->dev, "failed to unregister host1x client: %d\n",
			err);
		return err;
	}

	err = tegra_dc_rgb_remove(dc);
	if (err < 0) {
		dev_err(&pdev->dev, "failed to remove RGB output: %d\n", err);
		return err;
	}

	pm_runtime_disable(&pdev->dev);

	return 0;
}