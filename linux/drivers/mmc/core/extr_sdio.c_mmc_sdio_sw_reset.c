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
struct mmc_host {int /*<<< orphan*/  f_init; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmc_go_idle (struct mmc_host*) ; 
 int mmc_sdio_reinit_card (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_set_clock (struct mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_set_initial_signal_voltage (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_set_initial_state (struct mmc_host*) ; 
 int /*<<< orphan*/  sdio_reset (struct mmc_host*) ; 

__attribute__((used)) static int mmc_sdio_sw_reset(struct mmc_host *host)
{
	mmc_set_clock(host, host->f_init);
	sdio_reset(host);
	mmc_go_idle(host);

	mmc_set_initial_state(host);
	mmc_set_initial_signal_voltage(host);

	return mmc_sdio_reinit_card(host);
}