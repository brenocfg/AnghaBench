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
struct spear_sdhci {int card_int_gpio; struct sdhci_host* clk; } ;
struct sdhci_host {char* hw_name; scalar_t__ irq; int /*<<< orphan*/  mmc; int /*<<< orphan*/  quirks; int /*<<< orphan*/ * ops; struct sdhci_host* ioaddr; } ;
struct resource {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; struct device* parent; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct sdhci_host*) ; 
 int PTR_ERR (struct sdhci_host*) ; 
 int /*<<< orphan*/  SDHCI_QUIRK_BROKEN_ADMA ; 
 int /*<<< orphan*/  clk_disable_unprepare (struct sdhci_host*) ; 
 int clk_get_rate (struct sdhci_host*) ; 
 int clk_prepare_enable (struct sdhci_host*) ; 
 int clk_set_rate (struct sdhci_host*,int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct sdhci_host* devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 struct sdhci_host* devm_ioremap_resource (struct device*,struct resource*) ; 
 int mmc_gpio_request_cd (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sdhci_host*) ; 
 int sdhci_add_host (struct sdhci_host*) ; 
 struct sdhci_host* sdhci_alloc_host (struct device*,int) ; 
 int /*<<< orphan*/  sdhci_free_host (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_pltfm_ops ; 
 struct spear_sdhci* sdhci_priv (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_probe_config_dt (int /*<<< orphan*/ ,struct spear_sdhci*) ; 

__attribute__((used)) static int sdhci_probe(struct platform_device *pdev)
{
	struct sdhci_host *host;
	struct resource *iomem;
	struct spear_sdhci *sdhci;
	struct device *dev;
	int ret;

	dev = pdev->dev.parent ? pdev->dev.parent : &pdev->dev;
	host = sdhci_alloc_host(dev, sizeof(*sdhci));
	if (IS_ERR(host)) {
		ret = PTR_ERR(host);
		dev_dbg(&pdev->dev, "cannot allocate memory for sdhci\n");
		goto err;
	}

	iomem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	host->ioaddr = devm_ioremap_resource(&pdev->dev, iomem);
	if (IS_ERR(host->ioaddr)) {
		ret = PTR_ERR(host->ioaddr);
		dev_dbg(&pdev->dev, "unable to map iomem: %d\n", ret);
		goto err_host;
	}

	host->hw_name = "sdhci";
	host->ops = &sdhci_pltfm_ops;
	host->irq = platform_get_irq(pdev, 0);
	if (host->irq <= 0) {
		ret = -EINVAL;
		goto err_host;
	}
	host->quirks = SDHCI_QUIRK_BROKEN_ADMA;

	sdhci = sdhci_priv(host);

	/* clk enable */
	sdhci->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(sdhci->clk)) {
		ret = PTR_ERR(sdhci->clk);
		dev_dbg(&pdev->dev, "Error getting clock\n");
		goto err_host;
	}

	ret = clk_prepare_enable(sdhci->clk);
	if (ret) {
		dev_dbg(&pdev->dev, "Error enabling clock\n");
		goto err_host;
	}

	ret = clk_set_rate(sdhci->clk, 50000000);
	if (ret)
		dev_dbg(&pdev->dev, "Error setting desired clk, clk=%lu\n",
				clk_get_rate(sdhci->clk));

	sdhci_probe_config_dt(pdev->dev.of_node, sdhci);
	/*
	 * It is optional to use GPIOs for sdhci card detection. If
	 * sdhci->card_int_gpio < 0, then use original sdhci lines otherwise
	 * GPIO lines. We use the built-in GPIO support for this.
	 */
	if (sdhci->card_int_gpio >= 0) {
		ret = mmc_gpio_request_cd(host->mmc, sdhci->card_int_gpio, 0);
		if (ret < 0) {
			dev_dbg(&pdev->dev,
				"failed to request card-detect gpio%d\n",
				sdhci->card_int_gpio);
			goto disable_clk;
		}
	}

	ret = sdhci_add_host(host);
	if (ret)
		goto disable_clk;

	platform_set_drvdata(pdev, host);

	return 0;

disable_clk:
	clk_disable_unprepare(sdhci->clk);
err_host:
	sdhci_free_host(host);
err:
	dev_err(&pdev->dev, "spear-sdhci probe failed: %d\n", ret);
	return ret;
}