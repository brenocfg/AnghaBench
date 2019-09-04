#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct st_mmc_platform_data {struct sdhci_host* icnclk; struct sdhci_host* top_ioaddr; struct sdhci_host* rstc; } ;
struct sdhci_pltfm_host {struct sdhci_host* clk; } ;
struct sdhci_host {scalar_t__ ioaddr; int /*<<< orphan*/  mmc; } ;
struct resource {int dummy; } ;
struct reset_control {scalar_t__ ioaddr; int /*<<< orphan*/  mmc; } ;
struct TYPE_7__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;
struct clk {scalar_t__ ioaddr; int /*<<< orphan*/  mmc; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct sdhci_host*) ; 
 int PTR_ERR (struct sdhci_host*) ; 
 scalar_t__ SDHCI_HOST_VERSION ; 
 int SDHCI_SPEC_VER_MASK ; 
 int SDHCI_SPEC_VER_SHIFT ; 
 int SDHCI_VENDOR_VER_MASK ; 
 int SDHCI_VENDOR_VER_SHIFT ; 
 int /*<<< orphan*/  clk_disable_unprepare (struct sdhci_host*) ; 
 int clk_prepare_enable (struct sdhci_host*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*,int,int) ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*) ; 
 struct sdhci_host* devm_clk_get (TYPE_1__*,char*) ; 
 struct sdhci_host* devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 struct sdhci_host* devm_reset_control_get_exclusive (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int mmc_of_parse (int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int readw_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  reset_control_assert (struct sdhci_host*) ; 
 int /*<<< orphan*/  reset_control_deassert (struct sdhci_host*) ; 
 int sdhci_add_host (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_pltfm_free (struct platform_device*) ; 
 struct sdhci_host* sdhci_pltfm_init (struct platform_device*,int /*<<< orphan*/ *,int) ; 
 struct st_mmc_platform_data* sdhci_pltfm_priv (struct sdhci_pltfm_host*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_st_pdata ; 
 int /*<<< orphan*/  st_mmcss_cconfig (struct device_node*,struct sdhci_host*) ; 

__attribute__((used)) static int sdhci_st_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct sdhci_host *host;
	struct st_mmc_platform_data *pdata;
	struct sdhci_pltfm_host *pltfm_host;
	struct clk *clk, *icnclk;
	int ret = 0;
	u16 host_version;
	struct resource *res;
	struct reset_control *rstc;

	clk =  devm_clk_get(&pdev->dev, "mmc");
	if (IS_ERR(clk)) {
		dev_err(&pdev->dev, "Peripheral clk not found\n");
		return PTR_ERR(clk);
	}

	/* ICN clock isn't compulsory, but use it if it's provided. */
	icnclk = devm_clk_get(&pdev->dev, "icn");
	if (IS_ERR(icnclk))
		icnclk = NULL;

	rstc = devm_reset_control_get_exclusive(&pdev->dev, NULL);
	if (IS_ERR(rstc))
		rstc = NULL;
	else
		reset_control_deassert(rstc);

	host = sdhci_pltfm_init(pdev, &sdhci_st_pdata, sizeof(*pdata));
	if (IS_ERR(host)) {
		dev_err(&pdev->dev, "Failed sdhci_pltfm_init\n");
		ret = PTR_ERR(host);
		goto err_pltfm_init;
	}

	pltfm_host = sdhci_priv(host);
	pdata = sdhci_pltfm_priv(pltfm_host);
	pdata->rstc = rstc;

	ret = mmc_of_parse(host->mmc);
	if (ret) {
		dev_err(&pdev->dev, "Failed mmc_of_parse\n");
		goto err_of;
	}

	ret = clk_prepare_enable(clk);
	if (ret) {
		dev_err(&pdev->dev, "Failed to prepare clock\n");
		goto err_of;
	}

	ret = clk_prepare_enable(icnclk);
	if (ret) {
		dev_err(&pdev->dev, "Failed to prepare icn clock\n");
		goto err_icnclk;
	}

	/* Configure the FlashSS Top registers for setting eMMC TX/RX delay */
	res = platform_get_resource_byname(pdev, IORESOURCE_MEM,
					   "top-mmc-delay");
	pdata->top_ioaddr = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(pdata->top_ioaddr)) {
		dev_warn(&pdev->dev, "FlashSS Top Dly registers not available");
		pdata->top_ioaddr = NULL;
	}

	pltfm_host->clk = clk;
	pdata->icnclk = icnclk;

	/* Configure the Arasan HC inside the flashSS */
	st_mmcss_cconfig(np, host);

	ret = sdhci_add_host(host);
	if (ret)
		goto err_out;

	host_version = readw_relaxed((host->ioaddr + SDHCI_HOST_VERSION));

	dev_info(&pdev->dev, "SDHCI ST Initialised: Host Version: 0x%x Vendor Version 0x%x\n",
		((host_version & SDHCI_SPEC_VER_MASK) >> SDHCI_SPEC_VER_SHIFT),
		((host_version & SDHCI_VENDOR_VER_MASK) >>
		SDHCI_VENDOR_VER_SHIFT));

	return 0;

err_out:
	clk_disable_unprepare(icnclk);
err_icnclk:
	clk_disable_unprepare(clk);
err_of:
	sdhci_pltfm_free(pdev);
err_pltfm_init:
	if (rstc)
		reset_control_assert(rstc);

	return ret;
}