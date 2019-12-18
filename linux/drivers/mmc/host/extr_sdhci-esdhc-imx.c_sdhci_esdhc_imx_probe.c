#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sdhci_pltfm_host {struct sdhci_host* clk; int /*<<< orphan*/  clock; } ;
struct TYPE_7__ {int /*<<< orphan*/  hs400_enhanced_strobe; int /*<<< orphan*/  execute_tuning; } ;
struct sdhci_host {int tuning_delay; TYPE_4__* mmc; scalar_t__ ioaddr; TYPE_2__ mmc_host_ops; int /*<<< orphan*/  quirks2; int /*<<< orphan*/  quirks; } ;
struct pltfm_imx_data {int /*<<< orphan*/  pm_qos_req; struct esdhc_soc_data* socdata; struct sdhci_host* clk_per; struct sdhci_host* clk_ipg; struct sdhci_host* clk_ahb; struct sdhci_host* pins_default; struct sdhci_host* pinctrl; } ;
struct platform_device {int /*<<< orphan*/  dev; TYPE_1__* id_entry; } ;
struct of_device_id {struct esdhc_soc_data* data; } ;
struct esdhc_soc_data {int flags; } ;
struct cqhci_host {int /*<<< orphan*/ * ops; scalar_t__ mmio; } ;
struct TYPE_9__ {int caps; int caps2; } ;
struct TYPE_8__ {int /*<<< orphan*/  platform_execute_tuning; } ;
struct TYPE_6__ {scalar_t__ driver_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ ESDHC_CQHCI_ADDR_OFFSET ; 
 int ESDHC_FLAG_CQHCI ; 
 int ESDHC_FLAG_ERR004536 ; 
 int ESDHC_FLAG_HS200 ; 
 int ESDHC_FLAG_HS400 ; 
 int ESDHC_FLAG_HS400_ES ; 
 int ESDHC_FLAG_MAN_TUNING ; 
 int ESDHC_FLAG_PMQOS ; 
 scalar_t__ ESDHC_MIX_CTRL ; 
 scalar_t__ ESDHC_TUNE_CTRL_STATUS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct sdhci_host*) ; 
 int MMC_CAP2_CQE ; 
 int MMC_CAP2_CQE_DCMD ; 
 int MMC_CAP2_HS400_ES ; 
 int MMC_CAP_1_8V_DDR ; 
 int MMC_CAP_3_3V_DDR ; 
 int /*<<< orphan*/  PINCTRL_STATE_DEFAULT ; 
 int /*<<< orphan*/  PM_QOS_CPU_DMA_LATENCY ; 
 int PTR_ERR (struct sdhci_host*) ; 
 scalar_t__ SDHCI_AUTO_CMD_STATUS ; 
 int /*<<< orphan*/  SDHCI_QUIRK2_BROKEN_HS200 ; 
 int /*<<< orphan*/  SDHCI_QUIRK2_CAPS_BIT63_FOR_HS400 ; 
 int /*<<< orphan*/  SDHCI_QUIRK2_PRESET_VALUE_BROKEN ; 
 int /*<<< orphan*/  SDHCI_QUIRK_BROKEN_ADMA ; 
 int /*<<< orphan*/  clk_disable_unprepare (struct sdhci_host*) ; 
 int /*<<< orphan*/  clk_get_rate (struct sdhci_host*) ; 
 int clk_prepare_enable (struct sdhci_host*) ; 
 int cqhci_init (struct cqhci_host*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 void* devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 struct cqhci_host* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct sdhci_host* devm_pinctrl_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esdhc_cqhci_ops ; 
 int /*<<< orphan*/  esdhc_executing_tuning ; 
 int /*<<< orphan*/  esdhc_hs400_enhanced_strobe ; 
 scalar_t__ esdhc_is_usdhc (struct pltfm_imx_data*) ; 
 int /*<<< orphan*/  imx_esdhc_dt_ids ; 
 int /*<<< orphan*/  mmc_dev (TYPE_4__*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct sdhci_host* pinctrl_lookup_state (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_qos_add_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_qos_remove_request (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_suspend_ignore_children (int /*<<< orphan*/ *,int) ; 
 int sdhci_add_host (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_esdhc_imx_hwinit (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_esdhc_imx_pdata ; 
 int sdhci_esdhc_imx_probe_dt (struct platform_device*,struct sdhci_host*,struct pltfm_imx_data*) ; 
 int sdhci_esdhc_imx_probe_nondt (struct platform_device*,struct sdhci_host*,struct pltfm_imx_data*) ; 
 TYPE_3__ sdhci_esdhc_ops ; 
 int /*<<< orphan*/  sdhci_pltfm_free (struct platform_device*) ; 
 struct sdhci_host* sdhci_pltfm_init (struct platform_device*,int /*<<< orphan*/ *,int) ; 
 struct pltfm_imx_data* sdhci_pltfm_priv (struct sdhci_pltfm_host*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 
 int /*<<< orphan*/  usdhc_execute_tuning ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int sdhci_esdhc_imx_probe(struct platform_device *pdev)
{
	const struct of_device_id *of_id =
			of_match_device(imx_esdhc_dt_ids, &pdev->dev);
	struct sdhci_pltfm_host *pltfm_host;
	struct sdhci_host *host;
	struct cqhci_host *cq_host;
	int err;
	struct pltfm_imx_data *imx_data;

	host = sdhci_pltfm_init(pdev, &sdhci_esdhc_imx_pdata,
				sizeof(*imx_data));
	if (IS_ERR(host))
		return PTR_ERR(host);

	pltfm_host = sdhci_priv(host);

	imx_data = sdhci_pltfm_priv(pltfm_host);

	imx_data->socdata = of_id ? of_id->data : (struct esdhc_soc_data *)
						  pdev->id_entry->driver_data;

	if (imx_data->socdata->flags & ESDHC_FLAG_PMQOS)
		pm_qos_add_request(&imx_data->pm_qos_req,
			PM_QOS_CPU_DMA_LATENCY, 0);

	imx_data->clk_ipg = devm_clk_get(&pdev->dev, "ipg");
	if (IS_ERR(imx_data->clk_ipg)) {
		err = PTR_ERR(imx_data->clk_ipg);
		goto free_sdhci;
	}

	imx_data->clk_ahb = devm_clk_get(&pdev->dev, "ahb");
	if (IS_ERR(imx_data->clk_ahb)) {
		err = PTR_ERR(imx_data->clk_ahb);
		goto free_sdhci;
	}

	imx_data->clk_per = devm_clk_get(&pdev->dev, "per");
	if (IS_ERR(imx_data->clk_per)) {
		err = PTR_ERR(imx_data->clk_per);
		goto free_sdhci;
	}

	pltfm_host->clk = imx_data->clk_per;
	pltfm_host->clock = clk_get_rate(pltfm_host->clk);
	err = clk_prepare_enable(imx_data->clk_per);
	if (err)
		goto free_sdhci;
	err = clk_prepare_enable(imx_data->clk_ipg);
	if (err)
		goto disable_per_clk;
	err = clk_prepare_enable(imx_data->clk_ahb);
	if (err)
		goto disable_ipg_clk;

	imx_data->pinctrl = devm_pinctrl_get(&pdev->dev);
	if (IS_ERR(imx_data->pinctrl)) {
		err = PTR_ERR(imx_data->pinctrl);
		goto disable_ahb_clk;
	}

	imx_data->pins_default = pinctrl_lookup_state(imx_data->pinctrl,
						PINCTRL_STATE_DEFAULT);
	if (IS_ERR(imx_data->pins_default))
		dev_warn(mmc_dev(host->mmc), "could not get default state\n");

	if (esdhc_is_usdhc(imx_data)) {
		host->quirks2 |= SDHCI_QUIRK2_PRESET_VALUE_BROKEN;
		host->mmc->caps |= MMC_CAP_1_8V_DDR | MMC_CAP_3_3V_DDR;
		if (!(imx_data->socdata->flags & ESDHC_FLAG_HS200))
			host->quirks2 |= SDHCI_QUIRK2_BROKEN_HS200;

		/* clear tuning bits in case ROM has set it already */
		writel(0x0, host->ioaddr + ESDHC_MIX_CTRL);
		writel(0x0, host->ioaddr + SDHCI_AUTO_CMD_STATUS);
		writel(0x0, host->ioaddr + ESDHC_TUNE_CTRL_STATUS);

		/*
		 * Link usdhc specific mmc_host_ops execute_tuning function,
		 * to replace the standard one in sdhci_ops.
		 */
		host->mmc_host_ops.execute_tuning = usdhc_execute_tuning;
	}

	if (imx_data->socdata->flags & ESDHC_FLAG_MAN_TUNING)
		sdhci_esdhc_ops.platform_execute_tuning =
					esdhc_executing_tuning;

	if (imx_data->socdata->flags & ESDHC_FLAG_ERR004536)
		host->quirks |= SDHCI_QUIRK_BROKEN_ADMA;

	if (imx_data->socdata->flags & ESDHC_FLAG_HS400)
		host->quirks2 |= SDHCI_QUIRK2_CAPS_BIT63_FOR_HS400;

	if (imx_data->socdata->flags & ESDHC_FLAG_HS400_ES) {
		host->mmc->caps2 |= MMC_CAP2_HS400_ES;
		host->mmc_host_ops.hs400_enhanced_strobe =
					esdhc_hs400_enhanced_strobe;
	}

	if (imx_data->socdata->flags & ESDHC_FLAG_CQHCI) {
		host->mmc->caps2 |= MMC_CAP2_CQE | MMC_CAP2_CQE_DCMD;
		cq_host = devm_kzalloc(&pdev->dev, sizeof(*cq_host), GFP_KERNEL);
		if (!cq_host) {
			err = -ENOMEM;
			goto disable_ahb_clk;
		}

		cq_host->mmio = host->ioaddr + ESDHC_CQHCI_ADDR_OFFSET;
		cq_host->ops = &esdhc_cqhci_ops;

		err = cqhci_init(cq_host, host->mmc, false);
		if (err)
			goto disable_ahb_clk;
	}

	if (of_id)
		err = sdhci_esdhc_imx_probe_dt(pdev, host, imx_data);
	else
		err = sdhci_esdhc_imx_probe_nondt(pdev, host, imx_data);
	if (err)
		goto disable_ahb_clk;

	host->tuning_delay = 1;

	sdhci_esdhc_imx_hwinit(host);

	err = sdhci_add_host(host);
	if (err)
		goto disable_ahb_clk;

	pm_runtime_set_active(&pdev->dev);
	pm_runtime_set_autosuspend_delay(&pdev->dev, 50);
	pm_runtime_use_autosuspend(&pdev->dev);
	pm_suspend_ignore_children(&pdev->dev, 1);
	pm_runtime_enable(&pdev->dev);

	return 0;

disable_ahb_clk:
	clk_disable_unprepare(imx_data->clk_ahb);
disable_ipg_clk:
	clk_disable_unprepare(imx_data->clk_ipg);
disable_per_clk:
	clk_disable_unprepare(imx_data->clk_per);
free_sdhci:
	if (imx_data->socdata->flags & ESDHC_FLAG_PMQOS)
		pm_qos_remove_request(&imx_data->pm_qos_req);
	sdhci_pltfm_free(pdev);
	return err;
}