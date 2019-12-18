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
struct mmc_host {scalar_t__ use_spi_crc; } ;
struct mmc_command {int flags; scalar_t__ arg; int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 int MMC_CMD_BC ; 
 int /*<<< orphan*/  MMC_CS_DONTCARE ; 
 int /*<<< orphan*/  MMC_CS_HIGH ; 
 int /*<<< orphan*/  MMC_GO_IDLE_STATE ; 
 int MMC_RSP_NONE ; 
 int MMC_RSP_SPI_R1 ; 
 int /*<<< orphan*/  mmc_delay (int) ; 
 int /*<<< orphan*/  mmc_host_is_spi (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_set_chip_select (struct mmc_host*,int /*<<< orphan*/ ) ; 
 int mmc_wait_for_cmd (struct mmc_host*,struct mmc_command*,int /*<<< orphan*/ ) ; 

int mmc_go_idle(struct mmc_host *host)
{
	int err;
	struct mmc_command cmd = {};

	/*
	 * Non-SPI hosts need to prevent chipselect going active during
	 * GO_IDLE; that would put chips into SPI mode.  Remind them of
	 * that in case of hardware that won't pull up DAT3/nCS otherwise.
	 *
	 * SPI hosts ignore ios.chip_select; it's managed according to
	 * rules that must accommodate non-MMC slaves which this layer
	 * won't even know about.
	 */
	if (!mmc_host_is_spi(host)) {
		mmc_set_chip_select(host, MMC_CS_HIGH);
		mmc_delay(1);
	}

	cmd.opcode = MMC_GO_IDLE_STATE;
	cmd.arg = 0;
	cmd.flags = MMC_RSP_SPI_R1 | MMC_RSP_NONE | MMC_CMD_BC;

	err = mmc_wait_for_cmd(host, &cmd, 0);

	mmc_delay(1);

	if (!mmc_host_is_spi(host)) {
		mmc_set_chip_select(host, MMC_CS_DONTCARE);
		mmc_delay(1);
	}

	host->use_spi_crc = 0;

	return err;
}