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
struct TYPE_2__ {scalar_t__ power_mode; scalar_t__ vdd; scalar_t__ clock; } ;
struct mmc_host {TYPE_1__ ios; } ;

/* Variables and functions */
 scalar_t__ MMC_POWER_OFF ; 
 int /*<<< orphan*/  mmc_delay (int) ; 
 int /*<<< orphan*/  mmc_pwrseq_power_off (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_set_initial_state (struct mmc_host*) ; 

void mmc_power_off(struct mmc_host *host)
{
	if (host->ios.power_mode == MMC_POWER_OFF)
		return;

	mmc_pwrseq_power_off(host);

	host->ios.clock = 0;
	host->ios.vdd = 0;

	host->ios.power_mode = MMC_POWER_OFF;
	/* Set initial state and call mmc_set_ios */
	mmc_set_initial_state(host);

	/*
	 * Some configurations, such as the 802.11 SDIO card in the OLPC
	 * XO-1.5, require a short delay after poweroff before the card
	 * can be successfully turned on again.
	 */
	mmc_delay(1);
}