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
struct mmc_host {int caps2; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* get_ro ) (struct mmc_host*) ;} ;

/* Variables and functions */
 int MMC_CAP2_NO_WRITE_PROTECT ; 
 int stub1 (struct mmc_host*) ; 

__attribute__((used)) static int mmc_sd_get_ro(struct mmc_host *host)
{
	int ro;

	/*
	 * Some systems don't feature a write-protect pin and don't need one.
	 * E.g. because they only have micro-SD card slot. For those systems
	 * assume that the SD card is always read-write.
	 */
	if (host->caps2 & MMC_CAP2_NO_WRITE_PROTECT)
		return 0;

	if (!host->ops->get_ro)
		return -1;

	ro = host->ops->get_ro(host);

	return ro;
}