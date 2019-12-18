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
struct mmc_host {TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  ocr; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmc_claim_host (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_power_up (struct mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_release_host (struct mmc_host*) ; 
 int mmc_sdio_reinit_card (struct mmc_host*) ; 

__attribute__((used)) static int mmc_sdio_runtime_resume(struct mmc_host *host)
{
	int ret;

	/* Restore power and re-initialize. */
	mmc_claim_host(host);
	mmc_power_up(host, host->card->ocr);
	ret = mmc_sdio_reinit_card(host);
	mmc_release_host(host);

	return ret;
}