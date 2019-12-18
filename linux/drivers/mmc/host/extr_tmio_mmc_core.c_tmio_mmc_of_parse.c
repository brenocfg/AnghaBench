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
struct TYPE_2__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct mmc_host {int /*<<< orphan*/  caps2; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMC_CAP2_NO_WRITE_PROTECT ; 
 scalar_t__ of_get_property (struct device_node const*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tmio_mmc_of_parse(struct platform_device *pdev,
			      struct mmc_host *mmc)
{
	const struct device_node *np = pdev->dev.of_node;

	if (!np)
		return;

	/*
	 * DEPRECATED:
	 * For new platforms, please use "disable-wp" instead of
	 * "toshiba,mmc-wrprotect-disable"
	 */
	if (of_get_property(np, "toshiba,mmc-wrprotect-disable", NULL))
		mmc->caps2 |= MMC_CAP2_NO_WRITE_PROTECT;
}