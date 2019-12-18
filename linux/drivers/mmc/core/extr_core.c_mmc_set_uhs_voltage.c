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
struct mmc_host {TYPE_1__* ops; } ;
struct mmc_command {int flags; int* resp; scalar_t__ arg; int /*<<< orphan*/  opcode; } ;
struct TYPE_2__ {scalar_t__ (* card_busy ) (struct mmc_host*) ;int /*<<< orphan*/  start_signal_voltage_switch; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EIO ; 
 int EPERM ; 
 int MMC_CMD_AC ; 
 int MMC_RSP_R1 ; 
 int R1_ERROR ; 
 int /*<<< orphan*/  SD_SWITCH_VOLTAGE ; 
 int /*<<< orphan*/  mmc_delay (int) ; 
 int /*<<< orphan*/  mmc_host_is_spi (struct mmc_host*) ; 
 scalar_t__ mmc_host_set_uhs_voltage (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_hostname (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_power_cycle (struct mmc_host*,int /*<<< orphan*/ ) ; 
 int mmc_wait_for_cmd (struct mmc_host*,struct mmc_command*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct mmc_host*) ; 
 scalar_t__ stub2 (struct mmc_host*) ; 

int mmc_set_uhs_voltage(struct mmc_host *host, u32 ocr)
{
	struct mmc_command cmd = {};
	int err = 0;

	/*
	 * If we cannot switch voltages, return failure so the caller
	 * can continue without UHS mode
	 */
	if (!host->ops->start_signal_voltage_switch)
		return -EPERM;
	if (!host->ops->card_busy)
		pr_warn("%s: cannot verify signal voltage switch\n",
			mmc_hostname(host));

	cmd.opcode = SD_SWITCH_VOLTAGE;
	cmd.arg = 0;
	cmd.flags = MMC_RSP_R1 | MMC_CMD_AC;

	err = mmc_wait_for_cmd(host, &cmd, 0);
	if (err)
		return err;

	if (!mmc_host_is_spi(host) && (cmd.resp[0] & R1_ERROR))
		return -EIO;

	/*
	 * The card should drive cmd and dat[0:3] low immediately
	 * after the response of cmd11, but wait 1 ms to be sure
	 */
	mmc_delay(1);
	if (host->ops->card_busy && !host->ops->card_busy(host)) {
		err = -EAGAIN;
		goto power_cycle;
	}

	if (mmc_host_set_uhs_voltage(host)) {
		/*
		 * Voltages may not have been switched, but we've already
		 * sent CMD11, so a power cycle is required anyway
		 */
		err = -EAGAIN;
		goto power_cycle;
	}

	/* Wait for at least 1 ms according to spec */
	mmc_delay(1);

	/*
	 * Failure to switch is indicated by the card holding
	 * dat[0:3] low
	 */
	if (host->ops->card_busy && host->ops->card_busy(host))
		err = -EAGAIN;

power_cycle:
	if (err) {
		pr_debug("%s: Signal voltage switch failed, "
			"power cycling card\n", mmc_hostname(host));
		mmc_power_cycle(host, ocr);
	}

	return err;
}