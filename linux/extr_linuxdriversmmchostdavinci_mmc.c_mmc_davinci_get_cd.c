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
struct platform_device {int /*<<< orphan*/  id; TYPE_1__ dev; } ;
struct mmc_host {int /*<<< orphan*/  parent; } ;
struct davinci_mmc_config {int (* get_cd ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int mmc_gpio_get_cd (struct mmc_host*) ; 
 int stub1 (int /*<<< orphan*/ ) ; 
 struct platform_device* to_platform_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mmc_davinci_get_cd(struct mmc_host *mmc)
{
	struct platform_device *pdev = to_platform_device(mmc->parent);
	struct davinci_mmc_config *config = pdev->dev.platform_data;

	if (config && config->get_cd)
		return config->get_cd(pdev->id);

	return mmc_gpio_get_cd(mmc);
}