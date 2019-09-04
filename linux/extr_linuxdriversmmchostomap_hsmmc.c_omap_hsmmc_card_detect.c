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
struct omap_hsmmc_host {int /*<<< orphan*/  mmc; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct omap_hsmmc_host* dev_get_drvdata (struct device*) ; 
 int mmc_gpio_get_cd (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap_hsmmc_card_detect(struct device *dev)
{
	struct omap_hsmmc_host *host = dev_get_drvdata(dev);

	return mmc_gpio_get_cd(host->mmc);
}