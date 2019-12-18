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
struct TYPE_2__ {struct davinci_mmc_config* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct mmc_host {int caps; int f_min; int f_max; int /*<<< orphan*/  parent; } ;
struct mmc_davinci_host {scalar_t__ nr_sg; } ;
struct davinci_mmc_config {int wires; int max_freq; int caps; scalar_t__ nr_sg; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPROBE_DEFER ; 
 int MMC_CAP_4_BIT_DATA ; 
 int MMC_CAP_8_BIT_DATA ; 
 int MMC_CAP_NEEDS_POLL ; 
 int mmc_gpiod_request_cd (struct mmc_host*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int mmc_gpiod_request_ro (struct mmc_host*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct mmc_davinci_host* mmc_priv (struct mmc_host*) ; 
 struct platform_device* to_platform_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mmc_davinci_parse_pdata(struct mmc_host *mmc)
{
	struct platform_device *pdev = to_platform_device(mmc->parent);
	struct davinci_mmc_config *pdata = pdev->dev.platform_data;
	struct mmc_davinci_host *host;
	int ret;

	if (!pdata)
		return -EINVAL;

	host = mmc_priv(mmc);
	if (!host)
		return -EINVAL;

	if (pdata && pdata->nr_sg)
		host->nr_sg = pdata->nr_sg - 1;

	if (pdata && (pdata->wires == 4 || pdata->wires == 0))
		mmc->caps |= MMC_CAP_4_BIT_DATA;

	if (pdata && (pdata->wires == 8))
		mmc->caps |= (MMC_CAP_4_BIT_DATA | MMC_CAP_8_BIT_DATA);

	mmc->f_min = 312500;
	mmc->f_max = 25000000;
	if (pdata && pdata->max_freq)
		mmc->f_max = pdata->max_freq;
	if (pdata && pdata->caps)
		mmc->caps |= pdata->caps;

	/* Register a cd gpio, if there is not one, enable polling */
	ret = mmc_gpiod_request_cd(mmc, "cd", 0, false, 0, NULL);
	if (ret == -EPROBE_DEFER)
		return ret;
	else if (ret)
		mmc->caps |= MMC_CAP_NEEDS_POLL;

	ret = mmc_gpiod_request_ro(mmc, "wp", 0, 0, NULL);
	if (ret == -EPROBE_DEFER)
		return ret;

	return 0;
}