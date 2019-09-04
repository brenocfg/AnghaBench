#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct s3cmci_host {int /*<<< orphan*/  is2440; struct mmc_host* mmc; struct platform_device* pdev; } ;
struct s3c24xx_mci_pdata {int /*<<< orphan*/  gpio_wprotect; int /*<<< orphan*/  gpio_detect; scalar_t__ detect_invert; scalar_t__ wprotect_invert; scalar_t__ no_detect; scalar_t__ no_wprotect; } ;
struct TYPE_5__ {struct s3c24xx_mci_pdata* platform_data; } ;
struct platform_device {TYPE_2__ dev; } ;
struct mmc_host {int /*<<< orphan*/  caps2; int /*<<< orphan*/  caps; } ;
struct TYPE_4__ {int /*<<< orphan*/  driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMC_CAP2_CD_ACTIVE_HIGH ; 
 int /*<<< orphan*/  MMC_CAP2_NO_WRITE_PROTECT ; 
 int /*<<< orphan*/  MMC_CAP2_RO_ACTIVE_HIGH ; 
 int /*<<< orphan*/  MMC_CAP_NEEDS_POLL ; 
 int S3C2410_GPE (int) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 int /*<<< orphan*/  gpio_free (int) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int gpio_request (int,int /*<<< orphan*/ ) ; 
 int mmc_gpio_request_cd (struct mmc_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mmc_gpio_request_ro (struct mmc_host*,int /*<<< orphan*/ ) ; 
 TYPE_1__* platform_get_device_id (struct platform_device*) ; 
 struct s3c24xx_mci_pdata s3cmci_def_pdata ; 

__attribute__((used)) static int s3cmci_probe_pdata(struct s3cmci_host *host)
{
	struct platform_device *pdev = host->pdev;
	struct mmc_host *mmc = host->mmc;
	struct s3c24xx_mci_pdata *pdata;
	int i, ret;

	host->is2440 = platform_get_device_id(pdev)->driver_data;

	for (i = S3C2410_GPE(5); i <= S3C2410_GPE(10); i++) {
		ret = gpio_request(i, dev_name(&pdev->dev));
		if (ret) {
			dev_err(&pdev->dev, "failed to get gpio %d\n", i);

			for (i--; i >= S3C2410_GPE(5); i--)
				gpio_free(i);

			return ret;
		}
	}

	if (!pdev->dev.platform_data)
		pdev->dev.platform_data = &s3cmci_def_pdata;

	pdata = pdev->dev.platform_data;

	if (pdata->no_wprotect)
		mmc->caps2 |= MMC_CAP2_NO_WRITE_PROTECT;

	if (pdata->no_detect)
		mmc->caps |= MMC_CAP_NEEDS_POLL;

	if (pdata->wprotect_invert)
		mmc->caps2 |= MMC_CAP2_RO_ACTIVE_HIGH;

	if (pdata->detect_invert)
		 mmc->caps2 |= MMC_CAP2_CD_ACTIVE_HIGH;

	if (gpio_is_valid(pdata->gpio_detect)) {
		ret = mmc_gpio_request_cd(mmc, pdata->gpio_detect, 0);
		if (ret) {
			dev_err(&pdev->dev, "error requesting GPIO for CD %d\n",
				ret);
			return ret;
		}
	}

	if (gpio_is_valid(pdata->gpio_wprotect)) {
		ret = mmc_gpio_request_ro(mmc, pdata->gpio_wprotect);
		if (ret) {
			dev_err(&pdev->dev, "error requesting GPIO for WP %d\n",
				ret);
			return ret;
		}
	}

	return 0;
}