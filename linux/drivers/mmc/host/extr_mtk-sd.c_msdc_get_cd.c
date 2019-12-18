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
struct msdc_host {scalar_t__ base; int /*<<< orphan*/  internal_cd; } ;
struct mmc_host {int caps; int caps2; } ;

/* Variables and functions */
 int MMC_CAP2_CD_ACTIVE_HIGH ; 
 int MMC_CAP_NONREMOVABLE ; 
 scalar_t__ MSDC_PS ; 
 int MSDC_PS_CDSTS ; 
 int mmc_gpio_get_cd (struct mmc_host*) ; 
 struct msdc_host* mmc_priv (struct mmc_host*) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static int msdc_get_cd(struct mmc_host *mmc)
{
	struct msdc_host *host = mmc_priv(mmc);
	int val;

	if (mmc->caps & MMC_CAP_NONREMOVABLE)
		return 1;

	if (!host->internal_cd)
		return mmc_gpio_get_cd(mmc);

	val = readl(host->base + MSDC_PS) & MSDC_PS_CDSTS;
	if (mmc->caps2 & MMC_CAP2_CD_ACTIVE_HIGH)
		return !!val;
	else
		return !val;
}