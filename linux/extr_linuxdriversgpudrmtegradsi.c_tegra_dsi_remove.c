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
struct tegra_dsi {int /*<<< orphan*/  mipi; int /*<<< orphan*/  host; int /*<<< orphan*/  output; int /*<<< orphan*/  client; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int host1x_client_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mipi_dsi_host_unregister (int /*<<< orphan*/ *) ; 
 struct tegra_dsi* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tegra_mipi_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_output_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tegra_dsi_remove(struct platform_device *pdev)
{
	struct tegra_dsi *dsi = platform_get_drvdata(pdev);
	int err;

	pm_runtime_disable(&pdev->dev);

	err = host1x_client_unregister(&dsi->client);
	if (err < 0) {
		dev_err(&pdev->dev, "failed to unregister host1x client: %d\n",
			err);
		return err;
	}

	tegra_output_remove(&dsi->output);

	mipi_dsi_host_unregister(&dsi->host);
	tegra_mipi_free(dsi->mipi);

	return 0;
}