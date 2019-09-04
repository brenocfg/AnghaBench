#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sdhci_pltfm_host {struct sdhci_host* clk; } ;
struct sdhci_iproc_host {struct sdhci_iproc_data const* data; } ;
struct sdhci_iproc_data {int /*<<< orphan*/  caps1; int /*<<< orphan*/  caps; TYPE_1__* pdata; int /*<<< orphan*/  mmc_caps; } ;
struct sdhci_host {int /*<<< orphan*/  caps1; int /*<<< orphan*/  caps; TYPE_2__* mmc; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct of_device_id {struct sdhci_iproc_data* data; } ;
struct TYPE_4__ {int /*<<< orphan*/  caps; } ;
struct TYPE_3__ {int quirks; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct sdhci_host*) ; 
 int PTR_ERR (struct sdhci_host*) ; 
 int SDHCI_QUIRK_MISSING_CAPS ; 
 int /*<<< orphan*/  clk_disable_unprepare (struct sdhci_host*) ; 
 int clk_prepare_enable (struct sdhci_host*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct sdhci_host* devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mmc_of_parse (TYPE_2__*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sdhci_add_host (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_get_of_property (struct platform_device*) ; 
 int /*<<< orphan*/  sdhci_iproc_of_match ; 
 int /*<<< orphan*/  sdhci_pltfm_free (struct platform_device*) ; 
 struct sdhci_host* sdhci_pltfm_init (struct platform_device*,TYPE_1__*,int) ; 
 struct sdhci_iproc_host* sdhci_pltfm_priv (struct sdhci_pltfm_host*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 

__attribute__((used)) static int sdhci_iproc_probe(struct platform_device *pdev)
{
	const struct of_device_id *match;
	const struct sdhci_iproc_data *iproc_data;
	struct sdhci_host *host;
	struct sdhci_iproc_host *iproc_host;
	struct sdhci_pltfm_host *pltfm_host;
	int ret;

	match = of_match_device(sdhci_iproc_of_match, &pdev->dev);
	if (!match)
		return -EINVAL;
	iproc_data = match->data;

	host = sdhci_pltfm_init(pdev, iproc_data->pdata, sizeof(*iproc_host));
	if (IS_ERR(host))
		return PTR_ERR(host);

	pltfm_host = sdhci_priv(host);
	iproc_host = sdhci_pltfm_priv(pltfm_host);

	iproc_host->data = iproc_data;

	ret = mmc_of_parse(host->mmc);
	if (ret)
		goto err;

	sdhci_get_of_property(pdev);

	host->mmc->caps |= iproc_host->data->mmc_caps;

	pltfm_host->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(pltfm_host->clk)) {
		ret = PTR_ERR(pltfm_host->clk);
		goto err;
	}
	ret = clk_prepare_enable(pltfm_host->clk);
	if (ret) {
		dev_err(&pdev->dev, "failed to enable host clk\n");
		goto err;
	}

	if (iproc_host->data->pdata->quirks & SDHCI_QUIRK_MISSING_CAPS) {
		host->caps = iproc_host->data->caps;
		host->caps1 = iproc_host->data->caps1;
	}

	ret = sdhci_add_host(host);
	if (ret)
		goto err_clk;

	return 0;

err_clk:
	clk_disable_unprepare(pltfm_host->clk);
err:
	sdhci_pltfm_free(pdev);
	return ret;
}