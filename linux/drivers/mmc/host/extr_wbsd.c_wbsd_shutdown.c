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
struct wbsd_host {int dummy; } ;
struct mmc_host {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct mmc_host* dev_get_drvdata (struct device*) ; 
 struct wbsd_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_remove_host (struct mmc_host*) ; 
 int /*<<< orphan*/  wbsd_chip_poweroff (struct wbsd_host*) ; 
 int /*<<< orphan*/  wbsd_free_mmc (struct device*) ; 
 int /*<<< orphan*/  wbsd_release_resources (struct wbsd_host*) ; 

__attribute__((used)) static void wbsd_shutdown(struct device *dev, int pnp)
{
	struct mmc_host *mmc = dev_get_drvdata(dev);
	struct wbsd_host *host;

	if (!mmc)
		return;

	host = mmc_priv(mmc);

	mmc_remove_host(mmc);

	/*
	 * Power down the SD/MMC function.
	 */
	if (!pnp)
		wbsd_chip_poweroff(host);

	wbsd_release_resources(host);

	wbsd_free_mmc(dev);
}