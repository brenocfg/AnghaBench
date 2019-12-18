#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_13__ ;

/* Type definitions */
struct sdhci_sprd_host {int version; struct sdhci_host* clk_sdio; struct sdhci_host* clk_enable; struct sdhci_host* clk_2x_enable; int /*<<< orphan*/  flags; scalar_t__ base_rate; struct sdhci_host* pins_default; struct sdhci_host* pinctrl; struct sdhci_host* pins_uhs; } ;
struct TYPE_17__ {int /*<<< orphan*/  start_signal_voltage_switch; int /*<<< orphan*/  hs400_enhanced_strobe; int /*<<< orphan*/  request; } ;
struct sdhci_host {int version; int caps1; int /*<<< orphan*/  flags; void* caps; TYPE_13__* mmc; TYPE_1__ mmc_host_ops; int /*<<< orphan*/  dma_mask; } ;
struct TYPE_18__ {int /*<<< orphan*/  of_node; int /*<<< orphan*/ * dma_mask; } ;
struct platform_device {TYPE_2__ dev; } ;
struct clk {int version; int caps1; int /*<<< orphan*/  flags; void* caps; TYPE_13__* mmc; TYPE_1__ mmc_host_ops; int /*<<< orphan*/  dma_mask; } ;
struct TYPE_16__ {int caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 scalar_t__ IS_ERR (struct sdhci_host*) ; 
 int MMC_CAP_CMD23 ; 
 int MMC_CAP_ERASE ; 
 int MMC_CAP_MMC_HIGHSPEED ; 
 int MMC_CAP_SD_HIGHSPEED ; 
 int PTR_ERR (struct sdhci_host*) ; 
 int /*<<< orphan*/  SDHCI_CAPABILITIES ; 
 int /*<<< orphan*/  SDHCI_CAPABILITIES_1 ; 
 int /*<<< orphan*/  SDHCI_HOST_VERSION ; 
 scalar_t__ SDHCI_SPRD_CLK_DEF_RATE ; 
 int SDHCI_SUPPORT_DDR50 ; 
 int SDHCI_SUPPORT_SDR104 ; 
 int SDHCI_SUPPORT_SDR50 ; 
 int SDHCI_VENDOR_VER_MASK ; 
 int SDHCI_VENDOR_VER_SHIFT ; 
 struct sdhci_sprd_host* TO_SPRD_HOST (struct sdhci_host*) ; 
 int __sdhci_add_host (struct sdhci_host*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (struct sdhci_host*) ; 
 scalar_t__ clk_get_rate (struct sdhci_host*) ; 
 int clk_prepare_enable (struct sdhci_host*) ; 
 struct sdhci_host* devm_clk_get (TYPE_2__*,char*) ; 
 struct sdhci_host* devm_pinctrl_get (TYPE_2__*) ; 
 int mmc_of_parse (TYPE_13__*) ; 
 void* pinctrl_lookup_state (struct sdhci_host*,char*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (TYPE_2__*,int) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_suspend_ignore_children (TYPE_2__*,int) ; 
 int /*<<< orphan*/  sdhci_cleanup_host (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_enable_v4_mode (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_pltfm_free (struct platform_device*) ; 
 struct sdhci_host* sdhci_pltfm_init (struct platform_device*,int /*<<< orphan*/ *,int) ; 
 void* sdhci_readl (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int sdhci_readw (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int sdhci_setup_host (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_sprd_hs400_enhanced_strobe ; 
 int /*<<< orphan*/  sdhci_sprd_init_config (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_sprd_pdata ; 
 int /*<<< orphan*/  sdhci_sprd_phy_param_parse (struct sdhci_sprd_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_sprd_request ; 
 int /*<<< orphan*/  sdhci_sprd_voltage_switch ; 

__attribute__((used)) static int sdhci_sprd_probe(struct platform_device *pdev)
{
	struct sdhci_host *host;
	struct sdhci_sprd_host *sprd_host;
	struct clk *clk;
	int ret = 0;

	host = sdhci_pltfm_init(pdev, &sdhci_sprd_pdata, sizeof(*sprd_host));
	if (IS_ERR(host))
		return PTR_ERR(host);

	host->dma_mask = DMA_BIT_MASK(64);
	pdev->dev.dma_mask = &host->dma_mask;
	host->mmc_host_ops.request = sdhci_sprd_request;
	host->mmc_host_ops.hs400_enhanced_strobe =
		sdhci_sprd_hs400_enhanced_strobe;
	/*
	 * We can not use the standard ops to change and detect the voltage
	 * signal for Spreadtrum SD host controller, since our voltage regulator
	 * for I/O is fixed in hardware, that means we do not need control
	 * the standard SD host controller to change the I/O voltage.
	 */
	host->mmc_host_ops.start_signal_voltage_switch =
		sdhci_sprd_voltage_switch;

	host->mmc->caps = MMC_CAP_SD_HIGHSPEED | MMC_CAP_MMC_HIGHSPEED |
		MMC_CAP_ERASE | MMC_CAP_CMD23;
	ret = mmc_of_parse(host->mmc);
	if (ret)
		goto pltfm_free;

	sprd_host = TO_SPRD_HOST(host);
	sdhci_sprd_phy_param_parse(sprd_host, pdev->dev.of_node);

	sprd_host->pinctrl = devm_pinctrl_get(&pdev->dev);
	if (!IS_ERR(sprd_host->pinctrl)) {
		sprd_host->pins_uhs =
			pinctrl_lookup_state(sprd_host->pinctrl, "state_uhs");
		if (IS_ERR(sprd_host->pins_uhs)) {
			ret = PTR_ERR(sprd_host->pins_uhs);
			goto pltfm_free;
		}

		sprd_host->pins_default =
			pinctrl_lookup_state(sprd_host->pinctrl, "default");
		if (IS_ERR(sprd_host->pins_default)) {
			ret = PTR_ERR(sprd_host->pins_default);
			goto pltfm_free;
		}
	}

	clk = devm_clk_get(&pdev->dev, "sdio");
	if (IS_ERR(clk)) {
		ret = PTR_ERR(clk);
		goto pltfm_free;
	}
	sprd_host->clk_sdio = clk;
	sprd_host->base_rate = clk_get_rate(sprd_host->clk_sdio);
	if (!sprd_host->base_rate)
		sprd_host->base_rate = SDHCI_SPRD_CLK_DEF_RATE;

	clk = devm_clk_get(&pdev->dev, "enable");
	if (IS_ERR(clk)) {
		ret = PTR_ERR(clk);
		goto pltfm_free;
	}
	sprd_host->clk_enable = clk;

	clk = devm_clk_get(&pdev->dev, "2x_enable");
	if (!IS_ERR(clk))
		sprd_host->clk_2x_enable = clk;

	ret = clk_prepare_enable(sprd_host->clk_sdio);
	if (ret)
		goto pltfm_free;

	ret = clk_prepare_enable(sprd_host->clk_enable);
	if (ret)
		goto clk_disable;

	ret = clk_prepare_enable(sprd_host->clk_2x_enable);
	if (ret)
		goto clk_disable2;

	sdhci_sprd_init_config(host);
	host->version = sdhci_readw(host, SDHCI_HOST_VERSION);
	sprd_host->version = ((host->version & SDHCI_VENDOR_VER_MASK) >>
			       SDHCI_VENDOR_VER_SHIFT);

	pm_runtime_get_noresume(&pdev->dev);
	pm_runtime_set_active(&pdev->dev);
	pm_runtime_enable(&pdev->dev);
	pm_runtime_set_autosuspend_delay(&pdev->dev, 50);
	pm_runtime_use_autosuspend(&pdev->dev);
	pm_suspend_ignore_children(&pdev->dev, 1);

	sdhci_enable_v4_mode(host);

	/*
	 * Supply the existing CAPS, but clear the UHS-I modes. This
	 * will allow these modes to be specified only by device
	 * tree properties through mmc_of_parse().
	 */
	host->caps = sdhci_readl(host, SDHCI_CAPABILITIES);
	host->caps1 = sdhci_readl(host, SDHCI_CAPABILITIES_1);
	host->caps1 &= ~(SDHCI_SUPPORT_SDR50 | SDHCI_SUPPORT_SDR104 |
			 SDHCI_SUPPORT_DDR50);

	ret = sdhci_setup_host(host);
	if (ret)
		goto pm_runtime_disable;

	sprd_host->flags = host->flags;

	ret = __sdhci_add_host(host);
	if (ret)
		goto err_cleanup_host;

	pm_runtime_mark_last_busy(&pdev->dev);
	pm_runtime_put_autosuspend(&pdev->dev);

	return 0;

err_cleanup_host:
	sdhci_cleanup_host(host);

pm_runtime_disable:
	pm_runtime_put_noidle(&pdev->dev);
	pm_runtime_disable(&pdev->dev);
	pm_runtime_set_suspended(&pdev->dev);

	clk_disable_unprepare(sprd_host->clk_2x_enable);

clk_disable2:
	clk_disable_unprepare(sprd_host->clk_enable);

clk_disable:
	clk_disable_unprepare(sprd_host->clk_sdio);

pltfm_free:
	sdhci_pltfm_free(pdev);
	return ret;
}