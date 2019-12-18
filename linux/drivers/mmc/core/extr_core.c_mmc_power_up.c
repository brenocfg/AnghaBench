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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ power_mode; int /*<<< orphan*/  power_delay_ms; int /*<<< orphan*/  clock; scalar_t__ vdd; } ;
struct mmc_host {TYPE_1__ ios; int /*<<< orphan*/  f_init; } ;

/* Variables and functions */
 scalar_t__ MMC_POWER_ON ; 
 scalar_t__ MMC_POWER_UP ; 
 scalar_t__ fls (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_delay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_pwrseq_post_power_on (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_pwrseq_pre_power_on (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_set_initial_signal_voltage (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_set_initial_state (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_set_ios (struct mmc_host*) ; 

void mmc_power_up(struct mmc_host *host, u32 ocr)
{
	if (host->ios.power_mode == MMC_POWER_ON)
		return;

	mmc_pwrseq_pre_power_on(host);

	host->ios.vdd = fls(ocr) - 1;
	host->ios.power_mode = MMC_POWER_UP;
	/* Set initial state and call mmc_set_ios */
	mmc_set_initial_state(host);

	mmc_set_initial_signal_voltage(host);

	/*
	 * This delay should be sufficient to allow the power supply
	 * to reach the minimum voltage.
	 */
	mmc_delay(host->ios.power_delay_ms);

	mmc_pwrseq_post_power_on(host);

	host->ios.clock = host->f_init;

	host->ios.power_mode = MMC_POWER_ON;
	mmc_set_ios(host);

	/*
	 * This delay must be at least 74 clock sizes, or 1 ms, or the
	 * time required to reach a stable voltage.
	 */
	mmc_delay(host->ios.power_delay_ms);
}