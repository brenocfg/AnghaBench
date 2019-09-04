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
struct wbsd_host {int /*<<< orphan*/  ignore_timer; } ;
struct mmc_host {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 struct mmc_host* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmc_free_host (struct mmc_host*) ; 
 struct wbsd_host* mmc_priv (struct mmc_host*) ; 

__attribute__((used)) static void wbsd_free_mmc(struct device *dev)
{
	struct mmc_host *mmc;
	struct wbsd_host *host;

	mmc = dev_get_drvdata(dev);
	if (!mmc)
		return;

	host = mmc_priv(mmc);
	BUG_ON(host == NULL);

	del_timer_sync(&host->ignore_timer);

	mmc_free_host(mmc);

	dev_set_drvdata(dev, NULL);
}