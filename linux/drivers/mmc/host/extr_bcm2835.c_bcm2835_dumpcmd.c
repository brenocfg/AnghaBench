#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mmc_command {int /*<<< orphan*/  error; int /*<<< orphan*/ * resp; int /*<<< orphan*/  flags; int /*<<< orphan*/  arg; int /*<<< orphan*/  opcode; } ;
struct device {int dummy; } ;
struct bcm2835_host {struct mmc_command* cmd; TYPE_1__* pdev; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*,char,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm2835_dumpcmd(struct bcm2835_host *host, struct mmc_command *cmd,
			    const char *label)
{
	struct device *dev = &host->pdev->dev;

	if (!cmd)
		return;

	dev_dbg(dev, "%c%s op %d arg 0x%x flags 0x%x - resp %08x %08x %08x %08x, err %d\n",
		(cmd == host->cmd) ? '>' : ' ',
		label, cmd->opcode, cmd->arg, cmd->flags,
		cmd->resp[0], cmd->resp[1], cmd->resp[2], cmd->resp[3],
		cmd->error);
}