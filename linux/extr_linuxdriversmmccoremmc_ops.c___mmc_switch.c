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
typedef  int u8 ;
struct TYPE_2__ {unsigned char timing; } ;
struct mmc_host {unsigned int max_busy_timeout; int caps; TYPE_1__ ios; } ;
struct mmc_command {int arg; int flags; unsigned int busy_timeout; int sanitize_busy; int /*<<< orphan*/  opcode; } ;
struct mmc_card {struct mmc_host* host; } ;

/* Variables and functions */
 int EXT_CSD_SANITIZE_START ; 
 int MMC_CAP_WAIT_WHILE_BUSY ; 
 int MMC_CMD_AC ; 
 int /*<<< orphan*/  MMC_CMD_RETRIES ; 
 int MMC_RSP_R1 ; 
 int MMC_RSP_R1B ; 
 int MMC_RSP_SPI_R1 ; 
 int MMC_RSP_SPI_R1B ; 
 int /*<<< orphan*/  MMC_SWITCH ; 
 int MMC_SWITCH_MODE_WRITE_BYTE ; 
 scalar_t__ mmc_host_is_spi (struct mmc_host*) ; 
 int mmc_poll_for_busy (struct mmc_card*,unsigned int,int,int) ; 
 int /*<<< orphan*/  mmc_retune_hold (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_retune_release (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_set_timing (struct mmc_host*,unsigned char) ; 
 int mmc_switch_status (struct mmc_card*) ; 
 int mmc_wait_for_cmd (struct mmc_host*,struct mmc_command*,int /*<<< orphan*/ ) ; 

int __mmc_switch(struct mmc_card *card, u8 set, u8 index, u8 value,
		unsigned int timeout_ms, unsigned char timing,
		bool use_busy_signal, bool send_status,	bool retry_crc_err)
{
	struct mmc_host *host = card->host;
	int err;
	struct mmc_command cmd = {};
	bool use_r1b_resp = use_busy_signal;
	unsigned char old_timing = host->ios.timing;

	mmc_retune_hold(host);

	/*
	 * If the cmd timeout and the max_busy_timeout of the host are both
	 * specified, let's validate them. A failure means we need to prevent
	 * the host from doing hw busy detection, which is done by converting
	 * to a R1 response instead of a R1B.
	 */
	if (timeout_ms && host->max_busy_timeout &&
		(timeout_ms > host->max_busy_timeout))
		use_r1b_resp = false;

	cmd.opcode = MMC_SWITCH;
	cmd.arg = (MMC_SWITCH_MODE_WRITE_BYTE << 24) |
		  (index << 16) |
		  (value << 8) |
		  set;
	cmd.flags = MMC_CMD_AC;
	if (use_r1b_resp) {
		cmd.flags |= MMC_RSP_SPI_R1B | MMC_RSP_R1B;
		/*
		 * A busy_timeout of zero means the host can decide to use
		 * whatever value it finds suitable.
		 */
		cmd.busy_timeout = timeout_ms;
	} else {
		cmd.flags |= MMC_RSP_SPI_R1 | MMC_RSP_R1;
	}

	if (index == EXT_CSD_SANITIZE_START)
		cmd.sanitize_busy = true;

	err = mmc_wait_for_cmd(host, &cmd, MMC_CMD_RETRIES);
	if (err)
		goto out;

	/* No need to check card status in case of unblocking command */
	if (!use_busy_signal)
		goto out;

	/*If SPI or used HW busy detection above, then we don't need to poll. */
	if (((host->caps & MMC_CAP_WAIT_WHILE_BUSY) && use_r1b_resp) ||
		mmc_host_is_spi(host))
		goto out_tim;

	/* Let's try to poll to find out when the command is completed. */
	err = mmc_poll_for_busy(card, timeout_ms, send_status, retry_crc_err);
	if (err)
		goto out;

out_tim:
	/* Switch to new timing before check switch status. */
	if (timing)
		mmc_set_timing(host, timing);

	if (send_status) {
		err = mmc_switch_status(card);
		if (err && timing)
			mmc_set_timing(host, old_timing);
	}
out:
	mmc_retune_release(host);

	return err;
}