#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct mmc_host {int /*<<< orphan*/  caps2; } ;
struct jz4740_mmc_platform_data {int /*<<< orphan*/  power_active_low; int /*<<< orphan*/  gpio_power; int /*<<< orphan*/  read_only_active_low; int /*<<< orphan*/  card_detect_active_low; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  MMC_CAP2_CD_ACTIVE_HIGH ; 
 int /*<<< orphan*/  MMC_CAP2_RO_ACTIVE_HIGH ; 
 struct jz4740_mmc_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int jz4740_mmc_request_gpio (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int mmc_gpiod_request_cd (struct mmc_host*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int mmc_gpiod_request_ro (struct mmc_host*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int jz4740_mmc_request_gpios(struct mmc_host *mmc,
	struct platform_device *pdev)
{
	struct jz4740_mmc_platform_data *pdata = dev_get_platdata(&pdev->dev);
	int ret = 0;

	if (!pdata)
		return 0;

	if (!pdata->card_detect_active_low)
		mmc->caps2 |= MMC_CAP2_CD_ACTIVE_HIGH;
	if (!pdata->read_only_active_low)
		mmc->caps2 |= MMC_CAP2_RO_ACTIVE_HIGH;

	/*
	 * Get optional card detect and write protect GPIOs,
	 * only back out on probe deferral.
	 */
	ret = mmc_gpiod_request_cd(mmc, "cd", 0, false, 0, NULL);
	if (ret == -EPROBE_DEFER)
		return ret;

	ret = mmc_gpiod_request_ro(mmc, "wp", 0, false, 0, NULL);
	if (ret == -EPROBE_DEFER)
		return ret;

	return jz4740_mmc_request_gpio(&pdev->dev, pdata->gpio_power,
			"MMC read only", true, pdata->power_active_low);
}