#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sdhci_pltfm_host {int dummy; } ;
struct sdhci_host {int /*<<< orphan*/  mmc; } ;
struct TYPE_4__ {struct pic32_sdhci_platform_data* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct pic32_sdhci_priv {struct sdhci_host* sys_clk; struct sdhci_host* base_clk; } ;
struct pic32_sdhci_platform_data {int (* setup_dma ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ADMA_FIFO_RD_THSHLD ; 
 int /*<<< orphan*/  ADMA_FIFO_WR_THSHLD ; 
 scalar_t__ IS_ERR (struct sdhci_host*) ; 
 int PTR_ERR (struct sdhci_host*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (struct sdhci_host*) ; 
 int clk_prepare_enable (struct sdhci_host*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*) ; 
 void* devm_clk_get (TYPE_1__*,char*) ; 
 int mmc_of_parse (int /*<<< orphan*/ ) ; 
 int pic32_sdhci_probe_platform (struct platform_device*,struct pic32_sdhci_priv*) ; 
 int sdhci_add_host (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_pic32_pdata ; 
 int /*<<< orphan*/  sdhci_pltfm_free (struct platform_device*) ; 
 struct sdhci_host* sdhci_pltfm_init (struct platform_device*,int /*<<< orphan*/ *,int) ; 
 struct pic32_sdhci_priv* sdhci_pltfm_priv (struct sdhci_pltfm_host*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pic32_sdhci_probe(struct platform_device *pdev)
{
	struct sdhci_host *host;
	struct sdhci_pltfm_host *pltfm_host;
	struct pic32_sdhci_priv *sdhci_pdata;
	struct pic32_sdhci_platform_data *plat_data;
	int ret;

	host = sdhci_pltfm_init(pdev, &sdhci_pic32_pdata,
				sizeof(struct pic32_sdhci_priv));
	if (IS_ERR(host)) {
		ret = PTR_ERR(host);
		goto err;
	}

	pltfm_host = sdhci_priv(host);
	sdhci_pdata = sdhci_pltfm_priv(pltfm_host);

	plat_data = pdev->dev.platform_data;
	if (plat_data && plat_data->setup_dma) {
		ret = plat_data->setup_dma(ADMA_FIFO_RD_THSHLD,
					   ADMA_FIFO_WR_THSHLD);
		if (ret)
			goto err_host;
	}

	sdhci_pdata->sys_clk = devm_clk_get(&pdev->dev, "sys_clk");
	if (IS_ERR(sdhci_pdata->sys_clk)) {
		ret = PTR_ERR(sdhci_pdata->sys_clk);
		dev_err(&pdev->dev, "Error getting clock\n");
		goto err_host;
	}

	ret = clk_prepare_enable(sdhci_pdata->sys_clk);
	if (ret) {
		dev_err(&pdev->dev, "Error enabling clock\n");
		goto err_host;
	}

	sdhci_pdata->base_clk = devm_clk_get(&pdev->dev, "base_clk");
	if (IS_ERR(sdhci_pdata->base_clk)) {
		ret = PTR_ERR(sdhci_pdata->base_clk);
		dev_err(&pdev->dev, "Error getting clock\n");
		goto err_sys_clk;
	}

	ret = clk_prepare_enable(sdhci_pdata->base_clk);
	if (ret) {
		dev_err(&pdev->dev, "Error enabling clock\n");
		goto err_base_clk;
	}

	ret = mmc_of_parse(host->mmc);
	if (ret)
		goto err_base_clk;

	ret = pic32_sdhci_probe_platform(pdev, sdhci_pdata);
	if (ret) {
		dev_err(&pdev->dev, "failed to probe platform!\n");
		goto err_base_clk;
	}

	ret = sdhci_add_host(host);
	if (ret)
		goto err_base_clk;

	dev_info(&pdev->dev, "Successfully added sdhci host\n");
	return 0;

err_base_clk:
	clk_disable_unprepare(sdhci_pdata->base_clk);
err_sys_clk:
	clk_disable_unprepare(sdhci_pdata->sys_clk);
err_host:
	sdhci_pltfm_free(pdev);
err:
	dev_err(&pdev->dev, "pic32-sdhci probe failed: %d\n", ret);
	return ret;
}