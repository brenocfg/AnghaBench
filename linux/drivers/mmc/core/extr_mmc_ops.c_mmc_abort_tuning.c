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
typedef  scalar_t__ u32 ;
struct mmc_host {int dummy; } ;
struct mmc_command {int flags; int busy_timeout; int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 int MMC_CMD_AC ; 
 int MMC_RSP_R1 ; 
 int MMC_RSP_SPI_R1 ; 
 scalar_t__ MMC_SEND_TUNING_BLOCK_HS200 ; 
 int /*<<< orphan*/  MMC_STOP_TRANSMISSION ; 
 int mmc_wait_for_cmd (struct mmc_host*,struct mmc_command*,int /*<<< orphan*/ ) ; 

int mmc_abort_tuning(struct mmc_host *host, u32 opcode)
{
	struct mmc_command cmd = {};

	/*
	 * eMMC specification specifies that CMD12 can be used to stop a tuning
	 * command, but SD specification does not, so do nothing unless it is
	 * eMMC.
	 */
	if (opcode != MMC_SEND_TUNING_BLOCK_HS200)
		return 0;

	cmd.opcode = MMC_STOP_TRANSMISSION;
	cmd.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_AC;

	/*
	 * For drivers that override R1 to R1b, set an arbitrary timeout based
	 * on the tuning timeout i.e. 150ms.
	 */
	cmd.busy_timeout = 150;

	return mmc_wait_for_cmd(host, &cmd, 0);
}