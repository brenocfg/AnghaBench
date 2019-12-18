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
struct mmc_host {int /*<<< orphan*/  caps; int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMC_CAP_NONREMOVABLE ; 
 int /*<<< orphan*/  pm_runtime_forbid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void brcmf_sdiod_host_fixup(struct mmc_host *host)
{
	/* runtime-pm powers off the device */
	pm_runtime_forbid(host->parent);
	/* avoid removal detection upon resume */
	host->caps |= MMC_CAP_NONREMOVABLE;
}