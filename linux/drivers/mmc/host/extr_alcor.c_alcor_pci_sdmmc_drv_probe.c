#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct alcor_pci_priv* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct mmc_host {int dummy; } ;
struct alcor_sdmmc_host {int /*<<< orphan*/  timeout_work; int /*<<< orphan*/  cmd_mutex; struct alcor_pci_priv* alcor_pci; int /*<<< orphan*/  cur_power_mode; TYPE_1__* dev; } ;
struct alcor_pci_priv {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  AU6601_MS_INT_ENABLE ; 
 int /*<<< orphan*/  AU6601_REG_INT_ENABLE ; 
 int /*<<< orphan*/  DRV_NAME_ALCOR_PCI_SDMMC ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  MMC_POWER_UNDEFINED ; 
 int /*<<< orphan*/  alcor_hw_init (struct alcor_sdmmc_host*) ; 
 int /*<<< orphan*/  alcor_init_mmc (struct alcor_sdmmc_host*) ; 
 int /*<<< orphan*/  alcor_irq ; 
 int /*<<< orphan*/  alcor_irq_thread ; 
 int /*<<< orphan*/  alcor_timeout_timer ; 
 int /*<<< orphan*/  alcor_write32 (struct alcor_pci_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_1__*,struct alcor_sdmmc_host*) ; 
 int devm_request_threaded_irq (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct alcor_sdmmc_host*) ; 
 int /*<<< orphan*/  mmc_add_host (struct mmc_host*) ; 
 struct mmc_host* mmc_alloc_host (int,TYPE_1__*) ; 
 struct alcor_sdmmc_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int alcor_pci_sdmmc_drv_probe(struct platform_device *pdev)
{
	struct alcor_pci_priv *priv = pdev->dev.platform_data;
	struct mmc_host *mmc;
	struct alcor_sdmmc_host *host;
	int ret;

	mmc = mmc_alloc_host(sizeof(*host), &pdev->dev);
	if (!mmc) {
		dev_err(&pdev->dev, "Can't allocate MMC\n");
		return -ENOMEM;
	}

	host = mmc_priv(mmc);
	host->dev = &pdev->dev;
	host->cur_power_mode = MMC_POWER_UNDEFINED;
	host->alcor_pci = priv;

	/* make sure irqs are disabled */
	alcor_write32(priv, 0, AU6601_REG_INT_ENABLE);
	alcor_write32(priv, 0, AU6601_MS_INT_ENABLE);

	ret = devm_request_threaded_irq(&pdev->dev, priv->irq,
			alcor_irq, alcor_irq_thread, IRQF_SHARED,
			DRV_NAME_ALCOR_PCI_SDMMC, host);

	if (ret) {
		dev_err(&pdev->dev, "Failed to get irq for data line\n");
		return ret;
	}

	mutex_init(&host->cmd_mutex);
	INIT_DELAYED_WORK(&host->timeout_work, alcor_timeout_timer);

	alcor_init_mmc(host);
	alcor_hw_init(host);

	dev_set_drvdata(&pdev->dev, host);
	mmc_add_host(mmc);
	return 0;
}