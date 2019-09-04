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
struct sdio_func {TYPE_1__* card; } ;
struct mmc_host {int pm_caps; int pm_flags; } ;
typedef  int mmc_pm_flag_t ;
struct TYPE_2__ {struct mmc_host* host; } ;

/* Variables and functions */
 int EINVAL ; 

int sdio_set_host_pm_flags(struct sdio_func *func, mmc_pm_flag_t flags)
{
	struct mmc_host *host;

	if (!func)
		return -EINVAL;

	host = func->card->host;

	if (flags & ~host->pm_caps)
		return -EINVAL;

	/* function suspend methods are serialized, hence no lock needed */
	host->pm_flags |= flags;
	return 0;
}