#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sdhci_sirf_priv {int gpio_cd; } ;
struct sdhci_pltfm_host {struct sdhci_host* clk; } ;
struct sdhci_host {int /*<<< orphan*/  mmc; } ;
struct TYPE_3__ {scalar_t__ of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct clk {int /*<<< orphan*/  mmc; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct sdhci_host*) ; 
 int PTR_ERR (struct sdhci_host*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (struct sdhci_host*) ; 
 int clk_prepare_enable (struct sdhci_host*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 struct sdhci_host* devm_clk_get (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ gpio_is_valid (int) ; 
 int mmc_gpio_request_cd (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_gpiod_request_cd_irq (int /*<<< orphan*/ ) ; 
 int of_get_named_gpio (scalar_t__,char*,int /*<<< orphan*/ ) ; 
 int sdhci_add_host (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_get_of_property (struct platform_device*) ; 
 int /*<<< orphan*/  sdhci_pltfm_free (struct platform_device*) ; 
 struct sdhci_host* sdhci_pltfm_init (struct platform_device*,int /*<<< orphan*/ *,int) ; 
 struct sdhci_sirf_priv* sdhci_pltfm_priv (struct sdhci_pltfm_host*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_remove_host (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_sirf_pdata ; 

__attribute__((used)) static int sdhci_sirf_probe(struct platform_device *pdev)
{
	struct sdhci_host *host;
	struct sdhci_pltfm_host *pltfm_host;
	struct sdhci_sirf_priv *priv;
	struct clk *clk;
	int gpio_cd;
	int ret;

	clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(clk)) {
		dev_err(&pdev->dev, "unable to get clock");
		return PTR_ERR(clk);
	}

	if (pdev->dev.of_node)
		gpio_cd = of_get_named_gpio(pdev->dev.of_node, "cd-gpios", 0);
	else
		gpio_cd = -EINVAL;

	host = sdhci_pltfm_init(pdev, &sdhci_sirf_pdata, sizeof(struct sdhci_sirf_priv));
	if (IS_ERR(host))
		return PTR_ERR(host);

	pltfm_host = sdhci_priv(host);
	pltfm_host->clk = clk;
	priv = sdhci_pltfm_priv(pltfm_host);
	priv->gpio_cd = gpio_cd;

	sdhci_get_of_property(pdev);

	ret = clk_prepare_enable(pltfm_host->clk);
	if (ret)
		goto err_clk_prepare;

	ret = sdhci_add_host(host);
	if (ret)
		goto err_sdhci_add;

	/*
	 * We must request the IRQ after sdhci_add_host(), as the tasklet only
	 * gets setup in sdhci_add_host() and we oops.
	 */
	if (gpio_is_valid(priv->gpio_cd)) {
		ret = mmc_gpio_request_cd(host->mmc, priv->gpio_cd, 0);
		if (ret) {
			dev_err(&pdev->dev, "card detect irq request failed: %d\n",
				ret);
			goto err_request_cd;
		}
		mmc_gpiod_request_cd_irq(host->mmc);
	}

	return 0;

err_request_cd:
	sdhci_remove_host(host, 0);
err_sdhci_add:
	clk_disable_unprepare(pltfm_host->clk);
err_clk_prepare:
	sdhci_pltfm_free(pdev);
	return ret;
}