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
struct sdhci_pltfm_host {struct sdhci_host* clk; } ;
struct sdhci_host {int /*<<< orphan*/  mmc; } ;
struct resource {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct aspeed_sdhci {int /*<<< orphan*/  width_mask; int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASPEED_SDC_S0MMC8 ; 
 int /*<<< orphan*/  ASPEED_SDC_S1MMC8 ; 
 int EINVAL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct sdhci_host*) ; 
 int PTR_ERR (struct sdhci_host*) ; 
 int aspeed_sdhci_calculate_slot (struct aspeed_sdhci*,struct resource*) ; 
 int /*<<< orphan*/  aspeed_sdhci_pdata ; 
 int /*<<< orphan*/  clk_disable_unprepare (struct sdhci_host*) ; 
 int clk_prepare_enable (struct sdhci_host*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*,int) ; 
 struct sdhci_host* devm_clk_get (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int mmc_of_parse (int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sdhci_add_host (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_get_of_property (struct platform_device*) ; 
 int /*<<< orphan*/  sdhci_pltfm_free (struct platform_device*) ; 
 struct sdhci_host* sdhci_pltfm_init (struct platform_device*,int /*<<< orphan*/ *,int) ; 
 struct aspeed_sdhci* sdhci_pltfm_priv (struct sdhci_pltfm_host*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 

__attribute__((used)) static int aspeed_sdhci_probe(struct platform_device *pdev)
{
	struct sdhci_pltfm_host *pltfm_host;
	struct aspeed_sdhci *dev;
	struct sdhci_host *host;
	struct resource *res;
	int slot;
	int ret;

	host = sdhci_pltfm_init(pdev, &aspeed_sdhci_pdata, sizeof(*dev));
	if (IS_ERR(host))
		return PTR_ERR(host);

	pltfm_host = sdhci_priv(host);
	dev = sdhci_pltfm_priv(pltfm_host);
	dev->parent = dev_get_drvdata(pdev->dev.parent);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	slot = aspeed_sdhci_calculate_slot(dev, res);

	if (slot < 0)
		return slot;
	else if (slot >= 2)
		return -EINVAL;

	dev_info(&pdev->dev, "Configuring for slot %d\n", slot);
	dev->width_mask = !slot ? ASPEED_SDC_S0MMC8 : ASPEED_SDC_S1MMC8;

	sdhci_get_of_property(pdev);

	pltfm_host->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(pltfm_host->clk))
		return PTR_ERR(pltfm_host->clk);

	ret = clk_prepare_enable(pltfm_host->clk);
	if (ret) {
		dev_err(&pdev->dev, "Unable to enable SDIO clock\n");
		goto err_pltfm_free;
	}

	ret = mmc_of_parse(host->mmc);
	if (ret)
		goto err_sdhci_add;

	ret = sdhci_add_host(host);
	if (ret)
		goto err_sdhci_add;

	return 0;

err_sdhci_add:
	clk_disable_unprepare(pltfm_host->clk);
err_pltfm_free:
	sdhci_pltfm_free(pdev);
	return ret;
}