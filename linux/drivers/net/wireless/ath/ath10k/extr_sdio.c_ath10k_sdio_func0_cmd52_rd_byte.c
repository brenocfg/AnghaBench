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
struct mmc_command {int flags; unsigned char* resp; int /*<<< orphan*/  opcode; int /*<<< orphan*/  arg; } ;
struct mmc_card {int /*<<< orphan*/  host; } ;
typedef  int /*<<< orphan*/  io_cmd ;

/* Variables and functions */
 int MMC_CMD_AC ; 
 int MMC_RSP_R5 ; 
 int /*<<< orphan*/  SD_IO_RW_DIRECT ; 
 int /*<<< orphan*/  ath10k_sdio_set_cmd52_arg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct mmc_command*,int /*<<< orphan*/ ,int) ; 
 int mmc_wait_for_cmd (int /*<<< orphan*/ ,struct mmc_command*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath10k_sdio_func0_cmd52_rd_byte(struct mmc_card *card,
					   unsigned int address,
					   unsigned char *byte)
{
	struct mmc_command io_cmd;
	int ret;

	memset(&io_cmd, 0, sizeof(io_cmd));
	ath10k_sdio_set_cmd52_arg(&io_cmd.arg, 0, 0, address, 0);
	io_cmd.opcode = SD_IO_RW_DIRECT;
	io_cmd.flags = MMC_RSP_R5 | MMC_CMD_AC;

	ret = mmc_wait_for_cmd(card->host, &io_cmd, 0);
	if (!ret)
		*byte = io_cmd.resp[0];

	return ret;
}