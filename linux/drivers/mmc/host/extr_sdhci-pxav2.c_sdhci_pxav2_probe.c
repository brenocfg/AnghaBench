#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sdhci_pxa_platdata {int flags; int quirks; int host_caps; int pm_caps; } ;
struct sdhci_pltfm_host {struct sdhci_host* clk; } ;
struct sdhci_host {int quirks; int /*<<< orphan*/ * ops; TYPE_1__* mmc; } ;
struct device {struct sdhci_pxa_platdata* platform_data; } ;
struct platform_device {struct device dev; } ;
struct of_device_id {int dummy; } ;
struct clk {int quirks; int /*<<< orphan*/ * ops; TYPE_1__* mmc; } ;
struct TYPE_2__ {int caps; int pm_caps; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct sdhci_host*) ; 
 int MMC_CAP_8_BIT_DATA ; 
 int MMC_CAP_NONREMOVABLE ; 
 int PTR_ERR (struct sdhci_host*) ; 
 int PXA_FLAG_CARD_PERMANENT ; 
 int PXA_FLAG_SD_8_BIT_CAPABLE_SLOT ; 
 int SDHCI_QUIRK_BROKEN_ADMA ; 
 int SDHCI_QUIRK_BROKEN_CARD_DETECTION ; 
 int SDHCI_QUIRK_BROKEN_TIMEOUT_VAL ; 
 int SDHCI_QUIRK_CAP_CLOCK_BASE_BROKEN ; 
 int /*<<< orphan*/  clk_disable_unprepare (struct sdhci_host*) ; 
 int clk_prepare_enable (struct sdhci_host*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct sdhci_host* devm_clk_get (struct device*,char*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  of_match_ptr (int /*<<< orphan*/ ) ; 
 struct sdhci_pxa_platdata* pxav2_get_mmc_pdata (struct device*) ; 
 int /*<<< orphan*/  pxav2_sdhci_ops ; 
 int sdhci_add_host (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_pltfm_free (struct platform_device*) ; 
 struct sdhci_host* sdhci_pltfm_init (struct platform_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_pxav2_of_match ; 

__attribute__((used)) static int sdhci_pxav2_probe(struct platform_device *pdev)
{
	struct sdhci_pltfm_host *pltfm_host;
	struct sdhci_pxa_platdata *pdata = pdev->dev.platform_data;
	struct device *dev = &pdev->dev;
	struct sdhci_host *host = NULL;
	const struct of_device_id *match;

	int ret;
	struct clk *clk;

	host = sdhci_pltfm_init(pdev, NULL, 0);
	if (IS_ERR(host))
		return PTR_ERR(host);

	pltfm_host = sdhci_priv(host);

	clk = devm_clk_get(dev, "PXA-SDHCLK");
	if (IS_ERR(clk)) {
		dev_err(dev, "failed to get io clock\n");
		ret = PTR_ERR(clk);
		goto free;
	}
	pltfm_host->clk = clk;
	ret = clk_prepare_enable(clk);
	if (ret) {
		dev_err(&pdev->dev, "failed to enable io clock\n");
		goto free;
	}

	host->quirks = SDHCI_QUIRK_BROKEN_ADMA
		| SDHCI_QUIRK_BROKEN_TIMEOUT_VAL
		| SDHCI_QUIRK_CAP_CLOCK_BASE_BROKEN;

	match = of_match_device(of_match_ptr(sdhci_pxav2_of_match), &pdev->dev);
	if (match) {
		pdata = pxav2_get_mmc_pdata(dev);
	}
	if (pdata) {
		if (pdata->flags & PXA_FLAG_CARD_PERMANENT) {
			/* on-chip device */
			host->quirks |= SDHCI_QUIRK_BROKEN_CARD_DETECTION;
			host->mmc->caps |= MMC_CAP_NONREMOVABLE;
		}

		/* If slot design supports 8 bit data, indicate this to MMC. */
		if (pdata->flags & PXA_FLAG_SD_8_BIT_CAPABLE_SLOT)
			host->mmc->caps |= MMC_CAP_8_BIT_DATA;

		if (pdata->quirks)
			host->quirks |= pdata->quirks;
		if (pdata->host_caps)
			host->mmc->caps |= pdata->host_caps;
		if (pdata->pm_caps)
			host->mmc->pm_caps |= pdata->pm_caps;
	}

	host->ops = &pxav2_sdhci_ops;

	ret = sdhci_add_host(host);
	if (ret)
		goto disable_clk;

	return 0;

disable_clk:
	clk_disable_unprepare(clk);
free:
	sdhci_pltfm_free(pdev);
	return ret;
}