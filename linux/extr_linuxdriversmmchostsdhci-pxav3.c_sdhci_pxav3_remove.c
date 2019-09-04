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
struct sdhci_pxa {int /*<<< orphan*/  clk_core; int /*<<< orphan*/  clk_io; } ;
struct sdhci_pltfm_host {int dummy; } ;
struct sdhci_host {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct sdhci_host* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdhci_pltfm_free (struct platform_device*) ; 
 struct sdhci_pxa* sdhci_pltfm_priv (struct sdhci_pltfm_host*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_remove_host (struct sdhci_host*,int) ; 

__attribute__((used)) static int sdhci_pxav3_remove(struct platform_device *pdev)
{
	struct sdhci_host *host = platform_get_drvdata(pdev);
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct sdhci_pxa *pxa = sdhci_pltfm_priv(pltfm_host);

	pm_runtime_get_sync(&pdev->dev);
	pm_runtime_disable(&pdev->dev);
	pm_runtime_put_noidle(&pdev->dev);

	sdhci_remove_host(host, 1);

	clk_disable_unprepare(pxa->clk_io);
	clk_disable_unprepare(pxa->clk_core);

	sdhci_pltfm_free(pdev);

	return 0;
}