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
struct sdhci_pltfm_data {int dummy; } ;
struct sdhci_host {TYPE_1__* mmc; int /*<<< orphan*/  quirks; int /*<<< orphan*/  quirks2; } ;
struct sdhci_at91_priv {int restore_needed; struct sdhci_host* hclock; struct sdhci_host* mainck; struct sdhci_host* gck; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct of_device_id {struct sdhci_pltfm_data* data; } ;
struct TYPE_4__ {int caps; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct sdhci_host*) ; 
 int MMC_CAP_NEEDS_POLL ; 
 int MMC_CAP_NONREMOVABLE ; 
 int PTR_ERR (struct sdhci_host*) ; 
 int /*<<< orphan*/  SDHCI_QUIRK2_BROKEN_HS200 ; 
 int /*<<< orphan*/  SDHCI_QUIRK_BROKEN_CARD_DETECTION ; 
 int /*<<< orphan*/  clk_disable_unprepare (struct sdhci_host*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 void* devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ mmc_card_is_removable (TYPE_1__*) ; 
 scalar_t__ mmc_gpio_get_cd (TYPE_1__*) ; 
 int mmc_of_parse (TYPE_1__*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (int /*<<< orphan*/ *) ; 
 int sdhci_add_host (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_at91_dt_match ; 
 int sdhci_at91_set_clks_presets (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdhci_at91_set_force_card_detect (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_get_of_property (struct platform_device*) ; 
 int /*<<< orphan*/  sdhci_pltfm_free (struct platform_device*) ; 
 struct sdhci_host* sdhci_pltfm_init (struct platform_device*,struct sdhci_pltfm_data const*,int) ; 
 struct sdhci_at91_priv* sdhci_pltfm_priv (struct sdhci_pltfm_host*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 

__attribute__((used)) static int sdhci_at91_probe(struct platform_device *pdev)
{
	const struct of_device_id	*match;
	const struct sdhci_pltfm_data	*soc_data;
	struct sdhci_host		*host;
	struct sdhci_pltfm_host		*pltfm_host;
	struct sdhci_at91_priv		*priv;
	int				ret;

	match = of_match_device(sdhci_at91_dt_match, &pdev->dev);
	if (!match)
		return -EINVAL;
	soc_data = match->data;

	host = sdhci_pltfm_init(pdev, soc_data, sizeof(*priv));
	if (IS_ERR(host))
		return PTR_ERR(host);

	pltfm_host = sdhci_priv(host);
	priv = sdhci_pltfm_priv(pltfm_host);

	priv->mainck = devm_clk_get(&pdev->dev, "baseclk");
	if (IS_ERR(priv->mainck)) {
		dev_err(&pdev->dev, "failed to get baseclk\n");
		return PTR_ERR(priv->mainck);
	}

	priv->hclock = devm_clk_get(&pdev->dev, "hclock");
	if (IS_ERR(priv->hclock)) {
		dev_err(&pdev->dev, "failed to get hclock\n");
		return PTR_ERR(priv->hclock);
	}

	priv->gck = devm_clk_get(&pdev->dev, "multclk");
	if (IS_ERR(priv->gck)) {
		dev_err(&pdev->dev, "failed to get multclk\n");
		return PTR_ERR(priv->gck);
	}

	ret = sdhci_at91_set_clks_presets(&pdev->dev);
	if (ret)
		goto sdhci_pltfm_free;

	priv->restore_needed = false;

	ret = mmc_of_parse(host->mmc);
	if (ret)
		goto clocks_disable_unprepare;

	sdhci_get_of_property(pdev);

	pm_runtime_get_noresume(&pdev->dev);
	pm_runtime_set_active(&pdev->dev);
	pm_runtime_enable(&pdev->dev);
	pm_runtime_set_autosuspend_delay(&pdev->dev, 50);
	pm_runtime_use_autosuspend(&pdev->dev);

	/* HS200 is broken at this moment */
	host->quirks2 = SDHCI_QUIRK2_BROKEN_HS200;

	ret = sdhci_add_host(host);
	if (ret)
		goto pm_runtime_disable;

	/*
	 * When calling sdhci_runtime_suspend_host(), the sdhci layer makes
	 * the assumption that all the clocks of the controller are disabled.
	 * It means we can't get irq from it when it is runtime suspended.
	 * For that reason, it is not planned to wake-up on a card detect irq
	 * from the controller.
	 * If we want to use runtime PM and to be able to wake-up on card
	 * insertion, we have to use a GPIO for the card detection or we can
	 * use polling. Be aware that using polling will resume/suspend the
	 * controller between each attempt.
	 * Disable SDHCI_QUIRK_BROKEN_CARD_DETECTION to be sure nobody tries
	 * to enable polling via device tree with broken-cd property.
	 */
	if (mmc_card_is_removable(host->mmc) &&
	    mmc_gpio_get_cd(host->mmc) < 0) {
		host->mmc->caps |= MMC_CAP_NEEDS_POLL;
		host->quirks &= ~SDHCI_QUIRK_BROKEN_CARD_DETECTION;
	}

	/*
	 * If the device attached to the MMC bus is not removable, it is safer
	 * to set the Force Card Detect bit. People often don't connect the
	 * card detect signal and use this pin for another purpose. If the card
	 * detect pin is not muxed to SDHCI controller, a default value is
	 * used. This value can be different from a SoC revision to another
	 * one. Problems come when this default value is not card present. To
	 * avoid this case, if the device is non removable then the card
	 * detection procedure using the SDMCC_CD signal is bypassed.
	 * This bit is reset when a software reset for all command is performed
	 * so we need to implement our own reset function to set back this bit.
	 */
	if (host->mmc->caps & MMC_CAP_NONREMOVABLE)
		sdhci_at91_set_force_card_detect(host);

	pm_runtime_put_autosuspend(&pdev->dev);

	return 0;

pm_runtime_disable:
	pm_runtime_disable(&pdev->dev);
	pm_runtime_set_suspended(&pdev->dev);
	pm_runtime_put_noidle(&pdev->dev);
clocks_disable_unprepare:
	clk_disable_unprepare(priv->gck);
	clk_disable_unprepare(priv->mainck);
	clk_disable_unprepare(priv->hclock);
sdhci_pltfm_free:
	sdhci_pltfm_free(pdev);
	return ret;
}