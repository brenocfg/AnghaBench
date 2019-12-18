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
 int /*<<< orphan*/  mmc_power_cycle (struct mmc_host*,int /*<<< orphan*/ ) ; 
 int mmc_sd_init_card (struct mmc_host*,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int mmc_sd_hw_reset(struct mmc_host *host)
{
	mmc_power_cycle(host, host->card->ocr);
	return mmc_sd_init_card(host, host->card->ocr, host->card);
}