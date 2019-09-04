#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sdio_func {TYPE_2__* card; } ;
typedef  int /*<<< orphan*/  mmc_pm_flag_t ;
struct TYPE_4__ {TYPE_1__* host; } ;
struct TYPE_3__ {int /*<<< orphan*/  pm_caps; } ;

/* Variables and functions */

mmc_pm_flag_t sdio_get_host_pm_caps(struct sdio_func *func)
{
	if (!func)
		return 0;

	return func->card->host->pm_caps;
}