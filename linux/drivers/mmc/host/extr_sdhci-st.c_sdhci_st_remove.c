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
struct st_mmc_platform_data {int /*<<< orphan*/  icnclk; struct reset_control* rstc; } ;
struct sdhci_pltfm_host {int dummy; } ;
struct sdhci_host {int dummy; } ;
struct reset_control {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct sdhci_host* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  reset_control_assert (struct reset_control*) ; 
 struct st_mmc_platform_data* sdhci_pltfm_priv (struct sdhci_pltfm_host*) ; 
 int sdhci_pltfm_unregister (struct platform_device*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 

__attribute__((used)) static int sdhci_st_remove(struct platform_device *pdev)
{
	struct sdhci_host *host = platform_get_drvdata(pdev);
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct st_mmc_platform_data *pdata = sdhci_pltfm_priv(pltfm_host);
	struct reset_control *rstc = pdata->rstc;
	int ret;

	ret = sdhci_pltfm_unregister(pdev);

	clk_disable_unprepare(pdata->icnclk);

	if (rstc)
		reset_control_assert(rstc);

	return ret;
}