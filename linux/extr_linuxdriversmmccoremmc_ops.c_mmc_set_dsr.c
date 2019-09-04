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
struct mmc_host {int dsr; } ;
struct mmc_command {int arg; int flags; int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 int MMC_CMD_AC ; 
 int /*<<< orphan*/  MMC_CMD_RETRIES ; 
 int MMC_RSP_NONE ; 
 int /*<<< orphan*/  MMC_SET_DSR ; 
 int mmc_wait_for_cmd (struct mmc_host*,struct mmc_command*,int /*<<< orphan*/ ) ; 

int mmc_set_dsr(struct mmc_host *host)
{
	struct mmc_command cmd = {};

	cmd.opcode = MMC_SET_DSR;

	cmd.arg = (host->dsr << 16) | 0xffff;
	cmd.flags = MMC_RSP_NONE | MMC_CMD_AC;

	return mmc_wait_for_cmd(host, &cmd, MMC_CMD_RETRIES);
}