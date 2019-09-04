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
struct mmc_command {int flags; unsigned int busy_timeout; int /*<<< orphan*/  opcode; } ;
struct mmc_card {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int MMC_CMD_AC ; 
 int MMC_RSP_R1 ; 
 int MMC_RSP_SPI_R1 ; 
 int /*<<< orphan*/  MMC_STOP_TRANSMISSION ; 
 int mmc_wait_for_cmd (int /*<<< orphan*/ ,struct mmc_command*,int) ; 

__attribute__((used)) static int mmc_blk_send_stop(struct mmc_card *card, unsigned int timeout)
{
	struct mmc_command cmd = {
		.opcode = MMC_STOP_TRANSMISSION,
		.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_AC,
		/* Some hosts wait for busy anyway, so provide a busy timeout */
		.busy_timeout = timeout,
	};

	return mmc_wait_for_cmd(card->host, &cmd, 5);
}