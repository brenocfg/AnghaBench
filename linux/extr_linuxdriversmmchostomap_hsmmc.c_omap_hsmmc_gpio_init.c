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
struct omap_hsmmc_platform_data {int /*<<< orphan*/  gpio_wp; int /*<<< orphan*/  gpio_cd; int /*<<< orphan*/  gpio_cod; } ;
struct omap_hsmmc_host {int /*<<< orphan*/  card_detect; int /*<<< orphan*/  get_cover_state; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int mmc_gpio_request_cd (struct mmc_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mmc_gpio_request_ro (struct mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_gpio_set_cd_isr (struct mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_hsmmc_card_detect ; 
 int /*<<< orphan*/  omap_hsmmc_cover_irq ; 
 int /*<<< orphan*/  omap_hsmmc_get_cover_state ; 

__attribute__((used)) static int omap_hsmmc_gpio_init(struct mmc_host *mmc,
				struct omap_hsmmc_host *host,
				struct omap_hsmmc_platform_data *pdata)
{
	int ret;

	if (gpio_is_valid(pdata->gpio_cod)) {
		ret = mmc_gpio_request_cd(mmc, pdata->gpio_cod, 0);
		if (ret)
			return ret;

		host->get_cover_state = omap_hsmmc_get_cover_state;
		mmc_gpio_set_cd_isr(mmc, omap_hsmmc_cover_irq);
	} else if (gpio_is_valid(pdata->gpio_cd)) {
		ret = mmc_gpio_request_cd(mmc, pdata->gpio_cd, 0);
		if (ret)
			return ret;

		host->card_detect = omap_hsmmc_card_detect;
	}

	if (gpio_is_valid(pdata->gpio_wp)) {
		ret = mmc_gpio_request_ro(mmc, pdata->gpio_wp);
		if (ret)
			return ret;
	}

	return 0;
}