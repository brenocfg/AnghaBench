#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sdhci_tegra_soc_data {int nvquirks; int /*<<< orphan*/  pdata; } ;
struct sdhci_tegra {int ddr_signaling; int pad_calib_required; int pad_control_available; struct sdhci_host* rst; struct sdhci_host* power_gpio; struct sdhci_tegra_soc_data const* soc_data; } ;
struct sdhci_pltfm_host {struct sdhci_host* clk; } ;
struct TYPE_6__ {int /*<<< orphan*/  execute_tuning; int /*<<< orphan*/  hs400_enhanced_strobe; int /*<<< orphan*/  request; int /*<<< orphan*/  start_signal_voltage_switch; } ;
struct sdhci_host {TYPE_3__* mmc; TYPE_2__ mmc_host_ops; TYPE_1__* ops; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct of_device_id {struct sdhci_tegra_soc_data* data; } ;
struct clk {TYPE_3__* mmc; TYPE_2__ mmc_host_ops; TYPE_1__* ops; } ;
struct TYPE_7__ {int /*<<< orphan*/  caps; } ;
struct TYPE_5__ {int /*<<< orphan*/  platform_execute_tuning; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 scalar_t__ IS_ERR (struct sdhci_host*) ; 
 int /*<<< orphan*/  MMC_CAP_1_8V_DDR ; 
 int NVQUIRK_ENABLE_DDR50 ; 
 int NVQUIRK_HAS_PADCALIB ; 
 int NVQUIRK_NEEDS_PAD_CONTROL ; 
 int PTR_ERR (struct sdhci_host*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (struct sdhci_host*) ; 
 int /*<<< orphan*/  clk_prepare_enable (struct sdhci_host*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct sdhci_host* devm_clk_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct sdhci_host* devm_gpiod_get_optional (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct sdhci_host* devm_reset_control_get_exclusive (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mmc_dev (TYPE_3__*) ; 
 int mmc_of_parse (TYPE_3__*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int reset_control_assert (struct sdhci_host*) ; 
 int reset_control_deassert (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_pltfm_free (struct platform_device*) ; 
 struct sdhci_host* sdhci_pltfm_init (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 struct sdhci_tegra* sdhci_pltfm_priv (struct sdhci_pltfm_host*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 
 int sdhci_tegra_add_host (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_tegra_dt_match ; 
 int /*<<< orphan*/  sdhci_tegra_start_signal_voltage_switch ; 
 int /*<<< orphan*/  tegra_sdhci_execute_hw_tuning ; 
 int /*<<< orphan*/  tegra_sdhci_hs400_enhanced_strobe ; 
 int tegra_sdhci_init_pinctrl_info (int /*<<< orphan*/ *,struct sdhci_tegra*) ; 
 int /*<<< orphan*/  tegra_sdhci_parse_dt (struct sdhci_host*) ; 
 int /*<<< orphan*/  tegra_sdhci_request ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int sdhci_tegra_probe(struct platform_device *pdev)
{
	const struct of_device_id *match;
	const struct sdhci_tegra_soc_data *soc_data;
	struct sdhci_host *host;
	struct sdhci_pltfm_host *pltfm_host;
	struct sdhci_tegra *tegra_host;
	struct clk *clk;
	int rc;

	match = of_match_device(sdhci_tegra_dt_match, &pdev->dev);
	if (!match)
		return -EINVAL;
	soc_data = match->data;

	host = sdhci_pltfm_init(pdev, soc_data->pdata, sizeof(*tegra_host));
	if (IS_ERR(host))
		return PTR_ERR(host);
	pltfm_host = sdhci_priv(host);

	tegra_host = sdhci_pltfm_priv(pltfm_host);
	tegra_host->ddr_signaling = false;
	tegra_host->pad_calib_required = false;
	tegra_host->pad_control_available = false;
	tegra_host->soc_data = soc_data;

	if (soc_data->nvquirks & NVQUIRK_NEEDS_PAD_CONTROL) {
		rc = tegra_sdhci_init_pinctrl_info(&pdev->dev, tegra_host);
		if (rc == 0)
			host->mmc_host_ops.start_signal_voltage_switch =
				sdhci_tegra_start_signal_voltage_switch;
	}

	/* Hook to periodically rerun pad calibration */
	if (soc_data->nvquirks & NVQUIRK_HAS_PADCALIB)
		host->mmc_host_ops.request = tegra_sdhci_request;

	host->mmc_host_ops.hs400_enhanced_strobe =
			tegra_sdhci_hs400_enhanced_strobe;

	if (!host->ops->platform_execute_tuning)
		host->mmc_host_ops.execute_tuning =
				tegra_sdhci_execute_hw_tuning;

	rc = mmc_of_parse(host->mmc);
	if (rc)
		goto err_parse_dt;

	if (tegra_host->soc_data->nvquirks & NVQUIRK_ENABLE_DDR50)
		host->mmc->caps |= MMC_CAP_1_8V_DDR;

	tegra_sdhci_parse_dt(host);

	tegra_host->power_gpio = devm_gpiod_get_optional(&pdev->dev, "power",
							 GPIOD_OUT_HIGH);
	if (IS_ERR(tegra_host->power_gpio)) {
		rc = PTR_ERR(tegra_host->power_gpio);
		goto err_power_req;
	}

	clk = devm_clk_get(mmc_dev(host->mmc), NULL);
	if (IS_ERR(clk)) {
		rc = PTR_ERR(clk);

		if (rc != -EPROBE_DEFER)
			dev_err(&pdev->dev, "failed to get clock: %d\n", rc);

		goto err_clk_get;
	}
	clk_prepare_enable(clk);
	pltfm_host->clk = clk;

	tegra_host->rst = devm_reset_control_get_exclusive(&pdev->dev,
							   "sdhci");
	if (IS_ERR(tegra_host->rst)) {
		rc = PTR_ERR(tegra_host->rst);
		dev_err(&pdev->dev, "failed to get reset control: %d\n", rc);
		goto err_rst_get;
	}

	rc = reset_control_assert(tegra_host->rst);
	if (rc)
		goto err_rst_get;

	usleep_range(2000, 4000);

	rc = reset_control_deassert(tegra_host->rst);
	if (rc)
		goto err_rst_get;

	usleep_range(2000, 4000);

	rc = sdhci_tegra_add_host(host);
	if (rc)
		goto err_add_host;

	return 0;

err_add_host:
	reset_control_assert(tegra_host->rst);
err_rst_get:
	clk_disable_unprepare(pltfm_host->clk);
err_clk_get:
err_power_req:
err_parse_dt:
	sdhci_pltfm_free(pdev);
	return rc;
}