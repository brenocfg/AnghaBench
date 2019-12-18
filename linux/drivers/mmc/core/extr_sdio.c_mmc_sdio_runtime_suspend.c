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
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmc_claim_host (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_power_off (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_release_host (struct mmc_host*) ; 

__attribute__((used)) static int mmc_sdio_runtime_suspend(struct mmc_host *host)
{
	/* No references to the card, cut the power to it. */
	mmc_claim_host(host);
	mmc_power_off(host);
	mmc_release_host(host);

	return 0;
}