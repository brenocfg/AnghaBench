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
typedef  int u8 ;
typedef  int u32 ;
struct mmc_host {int dummy; } ;
struct mmc_command {int arg; int flags; int* resp; int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 int EIO ; 
 int MMC_CMD_BCR ; 
 int MMC_RSP_R7 ; 
 int MMC_RSP_SPI_R7 ; 
 int /*<<< orphan*/  SD_SEND_IF_COND ; 
 scalar_t__ mmc_host_is_spi (struct mmc_host*) ; 
 int mmc_wait_for_cmd (struct mmc_host*,struct mmc_command*,int /*<<< orphan*/ ) ; 

int mmc_send_if_cond(struct mmc_host *host, u32 ocr)
{
	struct mmc_command cmd = {};
	int err;
	static const u8 test_pattern = 0xAA;
	u8 result_pattern;

	/*
	 * To support SD 2.0 cards, we must always invoke SD_SEND_IF_COND
	 * before SD_APP_OP_COND. This command will harmlessly fail for
	 * SD 1.0 cards.
	 */
	cmd.opcode = SD_SEND_IF_COND;
	cmd.arg = ((ocr & 0xFF8000) != 0) << 8 | test_pattern;
	cmd.flags = MMC_RSP_SPI_R7 | MMC_RSP_R7 | MMC_CMD_BCR;

	err = mmc_wait_for_cmd(host, &cmd, 0);
	if (err)
		return err;

	if (mmc_host_is_spi(host))
		result_pattern = cmd.resp[1] & 0xFF;
	else
		result_pattern = cmd.resp[0] & 0xFF;

	if (result_pattern != test_pattern)
		return -EIO;

	return 0;
}