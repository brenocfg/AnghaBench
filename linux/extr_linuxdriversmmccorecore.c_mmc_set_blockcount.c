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
struct mmc_command {unsigned int arg; int flags; int /*<<< orphan*/  opcode; } ;
struct mmc_card {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int MMC_CMD_AC ; 
 int MMC_RSP_R1 ; 
 int MMC_RSP_SPI_R1 ; 
 int /*<<< orphan*/  MMC_SET_BLOCK_COUNT ; 
 int mmc_wait_for_cmd (int /*<<< orphan*/ ,struct mmc_command*,int) ; 

int mmc_set_blockcount(struct mmc_card *card, unsigned int blockcount,
			bool is_rel_write)
{
	struct mmc_command cmd = {};

	cmd.opcode = MMC_SET_BLOCK_COUNT;
	cmd.arg = blockcount & 0x0000FFFF;
	if (is_rel_write)
		cmd.arg |= 1 << 31;
	cmd.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_AC;
	return mmc_wait_for_cmd(card->host, &cmd, 5);
}