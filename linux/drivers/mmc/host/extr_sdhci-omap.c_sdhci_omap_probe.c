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
typedef  scalar_t__ u32 ;
struct soc_device_attribute {int dummy; } ;
struct sdhci_pltfm_host {struct sdhci_host* clk; } ;
struct sdhci_omap_host {char* version; int pbias_enabled; struct sdhci_host* pbias; int /*<<< orphan*/  flags; int /*<<< orphan*/  timing; int /*<<< orphan*/  power_mode; struct device* dev; int /*<<< orphan*/  base; struct sdhci_host* host; } ;
struct sdhci_omap_data {int /*<<< orphan*/  flags; scalar_t__ offset; } ;
struct TYPE_2__ {int /*<<< orphan*/  enable_sdio_irq; int /*<<< orphan*/  execute_tuning; int /*<<< orphan*/  card_busy; int /*<<< orphan*/  set_ios; int /*<<< orphan*/  start_signal_voltage_switch; } ;
struct sdhci_host {TYPE_1__ mmc_host_ops; struct mmc_host* mmc; int /*<<< orphan*/  ioaddr; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct of_device_id {scalar_t__ data; } ;
struct mmc_host {int f_max; int /*<<< orphan*/  caps2; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (struct sdhci_host*) ; 
 int /*<<< orphan*/  MMC_CAP2_NO_WRITE_PROTECT ; 
 int /*<<< orphan*/  MMC_POWER_UNDEFINED ; 
 int /*<<< orphan*/  MMC_TIMING_LEGACY ; 
 int PTR_ERR (struct sdhci_host*) ; 
 int __sdhci_add_host (struct sdhci_host*) ; 
 int clk_set_rate (struct sdhci_host*,int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 struct sdhci_host* devm_clk_get (struct device*,char*) ; 
 struct sdhci_host* devm_regulator_get_optional (struct device*,char*) ; 
 int /*<<< orphan*/  mmc_can_gpio_ro (struct mmc_host*) ; 
 int mmc_of_parse (struct mmc_host*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  omap_sdhci_match ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (struct device*) ; 
 int /*<<< orphan*/  sdhci_cleanup_host (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_get_of_property (struct platform_device*) ; 
 int /*<<< orphan*/  sdhci_omap_card_busy ; 
 int sdhci_omap_config_iodelay_pinctrl_state (struct sdhci_omap_host*) ; 
 int /*<<< orphan*/  sdhci_omap_enable_sdio_irq ; 
 int /*<<< orphan*/  sdhci_omap_execute_tuning ; 
 int /*<<< orphan*/  sdhci_omap_pdata ; 
 int sdhci_omap_set_capabilities (struct sdhci_omap_host*) ; 
 int /*<<< orphan*/  sdhci_omap_set_ios ; 
 int /*<<< orphan*/  sdhci_omap_soc_devices ; 
 int /*<<< orphan*/  sdhci_omap_start_signal_voltage_switch ; 
 int /*<<< orphan*/  sdhci_pltfm_free (struct platform_device*) ; 
 struct sdhci_host* sdhci_pltfm_init (struct platform_device*,int /*<<< orphan*/ *,int) ; 
 struct sdhci_omap_host* sdhci_pltfm_priv (struct sdhci_pltfm_host*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 
 int sdhci_setup_host (struct sdhci_host*) ; 
 struct soc_device_attribute* soc_device_match (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int sdhci_omap_probe(struct platform_device *pdev)
{
	int ret;
	u32 offset;
	struct device *dev = &pdev->dev;
	struct sdhci_host *host;
	struct sdhci_pltfm_host *pltfm_host;
	struct sdhci_omap_host *omap_host;
	struct mmc_host *mmc;
	const struct of_device_id *match;
	struct sdhci_omap_data *data;
	const struct soc_device_attribute *soc;

	match = of_match_device(omap_sdhci_match, dev);
	if (!match)
		return -EINVAL;

	data = (struct sdhci_omap_data *)match->data;
	if (!data) {
		dev_err(dev, "no sdhci omap data\n");
		return -EINVAL;
	}
	offset = data->offset;

	host = sdhci_pltfm_init(pdev, &sdhci_omap_pdata,
				sizeof(*omap_host));
	if (IS_ERR(host)) {
		dev_err(dev, "Failed sdhci_pltfm_init\n");
		return PTR_ERR(host);
	}

	pltfm_host = sdhci_priv(host);
	omap_host = sdhci_pltfm_priv(pltfm_host);
	omap_host->host = host;
	omap_host->base = host->ioaddr;
	omap_host->dev = dev;
	omap_host->power_mode = MMC_POWER_UNDEFINED;
	omap_host->timing = MMC_TIMING_LEGACY;
	omap_host->flags = data->flags;
	host->ioaddr += offset;

	mmc = host->mmc;
	sdhci_get_of_property(pdev);
	ret = mmc_of_parse(mmc);
	if (ret)
		goto err_pltfm_free;

	soc = soc_device_match(sdhci_omap_soc_devices);
	if (soc) {
		omap_host->version = "rev11";
		if (!strcmp(dev_name(dev), "4809c000.mmc"))
			mmc->f_max = 96000000;
		if (!strcmp(dev_name(dev), "480b4000.mmc"))
			mmc->f_max = 48000000;
		if (!strcmp(dev_name(dev), "480ad000.mmc"))
			mmc->f_max = 48000000;
	}

	if (!mmc_can_gpio_ro(mmc))
		mmc->caps2 |= MMC_CAP2_NO_WRITE_PROTECT;

	pltfm_host->clk = devm_clk_get(dev, "fck");
	if (IS_ERR(pltfm_host->clk)) {
		ret = PTR_ERR(pltfm_host->clk);
		goto err_pltfm_free;
	}

	ret = clk_set_rate(pltfm_host->clk, mmc->f_max);
	if (ret) {
		dev_err(dev, "failed to set clock to %d\n", mmc->f_max);
		goto err_pltfm_free;
	}

	omap_host->pbias = devm_regulator_get_optional(dev, "pbias");
	if (IS_ERR(omap_host->pbias)) {
		ret = PTR_ERR(omap_host->pbias);
		if (ret != -ENODEV)
			goto err_pltfm_free;
		dev_dbg(dev, "unable to get pbias regulator %d\n", ret);
	}
	omap_host->pbias_enabled = false;

	/*
	 * omap_device_pm_domain has callbacks to enable the main
	 * functional clock, interface clock and also configure the
	 * SYSCONFIG register of omap devices. The callback will be invoked
	 * as part of pm_runtime_get_sync.
	 */
	pm_runtime_enable(dev);
	ret = pm_runtime_get_sync(dev);
	if (ret < 0) {
		dev_err(dev, "pm_runtime_get_sync failed\n");
		pm_runtime_put_noidle(dev);
		goto err_rpm_disable;
	}

	ret = sdhci_omap_set_capabilities(omap_host);
	if (ret) {
		dev_err(dev, "failed to set system capabilities\n");
		goto err_put_sync;
	}

	host->mmc_host_ops.start_signal_voltage_switch =
					sdhci_omap_start_signal_voltage_switch;
	host->mmc_host_ops.set_ios = sdhci_omap_set_ios;
	host->mmc_host_ops.card_busy = sdhci_omap_card_busy;
	host->mmc_host_ops.execute_tuning = sdhci_omap_execute_tuning;
	host->mmc_host_ops.enable_sdio_irq = sdhci_omap_enable_sdio_irq;

	ret = sdhci_setup_host(host);
	if (ret)
		goto err_put_sync;

	ret = sdhci_omap_config_iodelay_pinctrl_state(omap_host);
	if (ret)
		goto err_cleanup_host;

	ret = __sdhci_add_host(host);
	if (ret)
		goto err_cleanup_host;

	return 0;

err_cleanup_host:
	sdhci_cleanup_host(host);

err_put_sync:
	pm_runtime_put_sync(dev);

err_rpm_disable:
	pm_runtime_disable(dev);

err_pltfm_free:
	sdhci_pltfm_free(pdev);
	return ret;
}