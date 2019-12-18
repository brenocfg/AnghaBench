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
typedef  int u32 ;
struct mmc_host {int dummy; } ;
struct mmc_command {int arg; int flags; int* resp; int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 int BIT (int) ; 
 int ETIMEDOUT ; 
 int MMC_CARD_BUSY ; 
 int MMC_CMD_BCR ; 
 int MMC_RSP_R3 ; 
 int MMC_RSP_SPI_R1 ; 
 int /*<<< orphan*/  MMC_SEND_OP_COND ; 
 int R1_SPI_IDLE ; 
 int /*<<< orphan*/  mmc_delay (int) ; 
 scalar_t__ mmc_host_is_spi (struct mmc_host*) ; 
 int mmc_wait_for_cmd (struct mmc_host*,struct mmc_command*,int /*<<< orphan*/ ) ; 

int mmc_send_op_cond(struct mmc_host *host, u32 ocr, u32 *rocr)
{
	struct mmc_command cmd = {};
	int i, err = 0;

	cmd.opcode = MMC_SEND_OP_COND;
	cmd.arg = mmc_host_is_spi(host) ? 0 : ocr;
	cmd.flags = MMC_RSP_SPI_R1 | MMC_RSP_R3 | MMC_CMD_BCR;

	for (i = 100; i; i--) {
		err = mmc_wait_for_cmd(host, &cmd, 0);
		if (err)
			break;

		/* wait until reset completes */
		if (mmc_host_is_spi(host)) {
			if (!(cmd.resp[0] & R1_SPI_IDLE))
				break;
		} else {
			if (cmd.resp[0] & MMC_CARD_BUSY)
				break;
		}

		err = -ETIMEDOUT;

		mmc_delay(10);

		/*
		 * According to eMMC specification v5.1 section 6.4.3, we
		 * should issue CMD1 repeatedly in the idle state until
		 * the eMMC is ready. Otherwise some eMMC devices seem to enter
		 * the inactive mode after mmc_init_card() issued CMD0 when
		 * the eMMC device is busy.
		 */
		if (!ocr && !mmc_host_is_spi(host))
			cmd.arg = cmd.resp[0] | BIT(30);
	}

	if (rocr && !mmc_host_is_spi(host))
		*rocr = cmd.resp[0];

	return err;
}