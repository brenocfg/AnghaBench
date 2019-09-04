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
typedef  int /*<<< orphan*/  u32 ;
struct mmc_command {int arg; int flags; int /*<<< orphan*/ * resp; int /*<<< orphan*/  opcode; } ;
struct mmc_card {int rca; int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int MMC_CMD_AC ; 
 int MMC_RSP_R1 ; 
 int MMC_RSP_SPI_R2 ; 
 int /*<<< orphan*/  MMC_SEND_STATUS ; 
 int /*<<< orphan*/  mmc_host_is_spi (int /*<<< orphan*/ ) ; 
 int mmc_wait_for_cmd (int /*<<< orphan*/ ,struct mmc_command*,unsigned int) ; 

int __mmc_send_status(struct mmc_card *card, u32 *status, unsigned int retries)
{
	int err;
	struct mmc_command cmd = {};

	cmd.opcode = MMC_SEND_STATUS;
	if (!mmc_host_is_spi(card->host))
		cmd.arg = card->rca << 16;
	cmd.flags = MMC_RSP_SPI_R2 | MMC_RSP_R1 | MMC_CMD_AC;

	err = mmc_wait_for_cmd(card->host, &cmd, retries);
	if (err)
		return err;

	/* NOTE: callers are required to understand the difference
	 * between "native" and SPI format status words!
	 */
	if (status)
		*status = cmd.resp[0];

	return 0;
}