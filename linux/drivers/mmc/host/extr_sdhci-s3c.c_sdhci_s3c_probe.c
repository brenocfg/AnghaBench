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
struct sdhci_s3c_drv_data {int sdhci_quirks; scalar_t__ no_divider; } ;
struct sdhci_s3c {int ext_cd_gpio; int cur_clk; struct sdhci_host* clk_io; scalar_t__ no_divider; int /*<<< orphan*/ * clk_rates; struct sdhci_host** clk_bus; struct s3c_sdhci_platdata* pdata; struct platform_device* pdev; struct sdhci_host* host; } ;
struct sdhci_host {char* hw_name; int quirks; int irq; TYPE_2__* mmc; scalar_t__ quirks2; TYPE_1__* ops; struct sdhci_host* ioaddr; } ;
struct s3c_sdhci_platdata {int max_width; scalar_t__ cd_type; int pm_caps; int host_caps; int host_caps2; int /*<<< orphan*/  (* cfg_gpio ) (struct platform_device*,int) ;} ;
struct resource {int dummy; } ;
struct device {int /*<<< orphan*/  platform_data; scalar_t__ of_node; } ;
struct platform_device {struct device dev; } ;
struct TYPE_4__ {int caps; int pm_caps; int caps2; } ;
struct TYPE_3__ {int /*<<< orphan*/  get_max_clock; int /*<<< orphan*/  get_min_clock; int /*<<< orphan*/  set_clock; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct sdhci_host*) ; 
 int MAX_BUS_CLK ; 
 int MMC_CAP_4_BIT_DATA ; 
 int MMC_CAP_8_BIT_DATA ; 
 int MMC_CAP_NONREMOVABLE ; 
 int PTR_ERR (struct sdhci_host*) ; 
 scalar_t__ S3C_SDHCI_CD_INTERNAL ; 
 scalar_t__ S3C_SDHCI_CD_NONE ; 
 scalar_t__ S3C_SDHCI_CD_PERMANENT ; 
 int SDHCI_QUIRK_32BIT_DMA_ADDR ; 
 int SDHCI_QUIRK_32BIT_DMA_SIZE ; 
 int SDHCI_QUIRK_BROKEN_ADMA_ZEROLEN_DESC ; 
 int SDHCI_QUIRK_BROKEN_CARD_DETECTION ; 
 int SDHCI_QUIRK_BROKEN_DMA ; 
 int SDHCI_QUIRK_DATA_TIMEOUT_USES_SDCLK ; 
 int SDHCI_QUIRK_MULTIBLOCK_READ_ACMD12 ; 
 int SDHCI_QUIRK_NO_BUSY_IRQ ; 
 int SDHCI_QUIRK_NO_ENDATTR_IN_NOPDESC ; 
 int SDHCI_QUIRK_NO_HISPD_BIT ; 
 int /*<<< orphan*/  clk_disable_unprepare (struct sdhci_host*) ; 
 int /*<<< orphan*/  clk_get_rate (struct sdhci_host*) ; 
 int /*<<< orphan*/  clk_prepare_enable (struct sdhci_host*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int,char*,int /*<<< orphan*/ ) ; 
 void* devm_clk_get (struct device*,char*) ; 
 struct sdhci_host* devm_ioremap_resource (struct device*,struct resource*) ; 
 struct s3c_sdhci_platdata* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct s3c_sdhci_platdata*,int /*<<< orphan*/ ,int) ; 
 int mmc_of_parse (TYPE_2__*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sdhci_host*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (struct device*,int) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (struct device*) ; 
 int /*<<< orphan*/  pm_suspend_ignore_children (struct device*,int) ; 
 int sdhci_add_host (struct sdhci_host*) ; 
 struct sdhci_host* sdhci_alloc_host (struct device*,int) ; 
 int /*<<< orphan*/  sdhci_cmu_get_max_clock ; 
 int /*<<< orphan*/  sdhci_cmu_get_min_clock ; 
 int /*<<< orphan*/  sdhci_cmu_set_clock ; 
 int /*<<< orphan*/  sdhci_free_host (struct sdhci_host*) ; 
 struct sdhci_s3c* sdhci_priv (struct sdhci_host*) ; 
 struct sdhci_s3c_drv_data* sdhci_s3c_get_driver_data (struct platform_device*) ; 
 TYPE_1__ sdhci_s3c_ops ; 
 int sdhci_s3c_parse_dt (struct device*,struct sdhci_host*,struct s3c_sdhci_platdata*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  stub1 (struct platform_device*,int) ; 

__attribute__((used)) static int sdhci_s3c_probe(struct platform_device *pdev)
{
	struct s3c_sdhci_platdata *pdata;
	struct sdhci_s3c_drv_data *drv_data;
	struct device *dev = &pdev->dev;
	struct sdhci_host *host;
	struct sdhci_s3c *sc;
	struct resource *res;
	int ret, irq, ptr, clks;

	if (!pdev->dev.platform_data && !pdev->dev.of_node) {
		dev_err(dev, "no device data specified\n");
		return -ENOENT;
	}

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;

	host = sdhci_alloc_host(dev, sizeof(struct sdhci_s3c));
	if (IS_ERR(host)) {
		dev_err(dev, "sdhci_alloc_host() failed\n");
		return PTR_ERR(host);
	}
	sc = sdhci_priv(host);

	pdata = devm_kzalloc(&pdev->dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata) {
		ret = -ENOMEM;
		goto err_pdata_io_clk;
	}

	if (pdev->dev.of_node) {
		ret = sdhci_s3c_parse_dt(&pdev->dev, host, pdata);
		if (ret)
			goto err_pdata_io_clk;
	} else {
		memcpy(pdata, pdev->dev.platform_data, sizeof(*pdata));
		sc->ext_cd_gpio = -1; /* invalid gpio number */
	}

	drv_data = sdhci_s3c_get_driver_data(pdev);

	sc->host = host;
	sc->pdev = pdev;
	sc->pdata = pdata;
	sc->cur_clk = -1;

	platform_set_drvdata(pdev, host);

	sc->clk_io = devm_clk_get(dev, "hsmmc");
	if (IS_ERR(sc->clk_io)) {
		dev_err(dev, "failed to get io clock\n");
		ret = PTR_ERR(sc->clk_io);
		goto err_pdata_io_clk;
	}

	/* enable the local io clock and keep it running for the moment. */
	clk_prepare_enable(sc->clk_io);

	for (clks = 0, ptr = 0; ptr < MAX_BUS_CLK; ptr++) {
		char name[14];

		snprintf(name, 14, "mmc_busclk.%d", ptr);
		sc->clk_bus[ptr] = devm_clk_get(dev, name);
		if (IS_ERR(sc->clk_bus[ptr]))
			continue;

		clks++;
		sc->clk_rates[ptr] = clk_get_rate(sc->clk_bus[ptr]);

		dev_info(dev, "clock source %d: %s (%ld Hz)\n",
				ptr, name, sc->clk_rates[ptr]);
	}

	if (clks == 0) {
		dev_err(dev, "failed to find any bus clocks\n");
		ret = -ENOENT;
		goto err_no_busclks;
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	host->ioaddr = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(host->ioaddr)) {
		ret = PTR_ERR(host->ioaddr);
		goto err_req_regs;
	}

	/* Ensure we have minimal gpio selected CMD/CLK/Detect */
	if (pdata->cfg_gpio)
		pdata->cfg_gpio(pdev, pdata->max_width);

	host->hw_name = "samsung-hsmmc";
	host->ops = &sdhci_s3c_ops;
	host->quirks = 0;
	host->quirks2 = 0;
	host->irq = irq;

	/* Setup quirks for the controller */
	host->quirks |= SDHCI_QUIRK_NO_ENDATTR_IN_NOPDESC;
	host->quirks |= SDHCI_QUIRK_NO_HISPD_BIT;
	if (drv_data) {
		host->quirks |= drv_data->sdhci_quirks;
		sc->no_divider = drv_data->no_divider;
	}

#ifndef CONFIG_MMC_SDHCI_S3C_DMA

	/* we currently see overruns on errors, so disable the SDMA
	 * support as well. */
	host->quirks |= SDHCI_QUIRK_BROKEN_DMA;

#endif /* CONFIG_MMC_SDHCI_S3C_DMA */

	/* It seems we do not get an DATA transfer complete on non-busy
	 * transfers, not sure if this is a problem with this specific
	 * SDHCI block, or a missing configuration that needs to be set. */
	host->quirks |= SDHCI_QUIRK_NO_BUSY_IRQ;

	/* This host supports the Auto CMD12 */
	host->quirks |= SDHCI_QUIRK_MULTIBLOCK_READ_ACMD12;

	/* Samsung SoCs need BROKEN_ADMA_ZEROLEN_DESC */
	host->quirks |= SDHCI_QUIRK_BROKEN_ADMA_ZEROLEN_DESC;

	if (pdata->cd_type == S3C_SDHCI_CD_NONE ||
	    pdata->cd_type == S3C_SDHCI_CD_PERMANENT)
		host->quirks |= SDHCI_QUIRK_BROKEN_CARD_DETECTION;

	if (pdata->cd_type == S3C_SDHCI_CD_PERMANENT)
		host->mmc->caps = MMC_CAP_NONREMOVABLE;

	switch (pdata->max_width) {
	case 8:
		host->mmc->caps |= MMC_CAP_8_BIT_DATA;
		/* Fall through */
	case 4:
		host->mmc->caps |= MMC_CAP_4_BIT_DATA;
		break;
	}

	if (pdata->pm_caps)
		host->mmc->pm_caps |= pdata->pm_caps;

	host->quirks |= (SDHCI_QUIRK_32BIT_DMA_ADDR |
			 SDHCI_QUIRK_32BIT_DMA_SIZE);

	/* HSMMC on Samsung SoCs uses SDCLK as timeout clock */
	host->quirks |= SDHCI_QUIRK_DATA_TIMEOUT_USES_SDCLK;

	/*
	 * If controller does not have internal clock divider,
	 * we can use overriding functions instead of default.
	 */
	if (sc->no_divider) {
		sdhci_s3c_ops.set_clock = sdhci_cmu_set_clock;
		sdhci_s3c_ops.get_min_clock = sdhci_cmu_get_min_clock;
		sdhci_s3c_ops.get_max_clock = sdhci_cmu_get_max_clock;
	}

	/* It supports additional host capabilities if needed */
	if (pdata->host_caps)
		host->mmc->caps |= pdata->host_caps;

	if (pdata->host_caps2)
		host->mmc->caps2 |= pdata->host_caps2;

	pm_runtime_enable(&pdev->dev);
	pm_runtime_set_autosuspend_delay(&pdev->dev, 50);
	pm_runtime_use_autosuspend(&pdev->dev);
	pm_suspend_ignore_children(&pdev->dev, 1);

	ret = mmc_of_parse(host->mmc);
	if (ret)
		goto err_req_regs;

	ret = sdhci_add_host(host);
	if (ret)
		goto err_req_regs;

#ifdef CONFIG_PM
	if (pdata->cd_type != S3C_SDHCI_CD_INTERNAL)
		clk_disable_unprepare(sc->clk_io);
#endif
	return 0;

 err_req_regs:
	pm_runtime_disable(&pdev->dev);

 err_no_busclks:
	clk_disable_unprepare(sc->clk_io);

 err_pdata_io_clk:
	sdhci_free_host(host);

	return ret;
}