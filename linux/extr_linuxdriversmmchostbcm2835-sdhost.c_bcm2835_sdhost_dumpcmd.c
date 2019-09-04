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
struct mmc_command {int /*<<< orphan*/  error; int /*<<< orphan*/ * resp; int /*<<< orphan*/  flags; int /*<<< orphan*/  arg; int /*<<< orphan*/  opcode; } ;
struct bcm2835_host {struct mmc_command* cmd; int /*<<< orphan*/  mmc; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,char,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm2835_sdhost_dumpcmd(struct bcm2835_host *host,
				   struct mmc_command *cmd,
				   const char *label)
{
	if (cmd)
		pr_info("%s:%c%s op %d arg 0x%x flags 0x%x - resp %08x %08x %08x %08x, err %d\n",
			mmc_hostname(host->mmc),
			(cmd == host->cmd) ? '>' : ' ',
			label, cmd->opcode, cmd->arg, cmd->flags,
			cmd->resp[0], cmd->resp[1], cmd->resp[2], cmd->resp[3],
			cmd->error);
}