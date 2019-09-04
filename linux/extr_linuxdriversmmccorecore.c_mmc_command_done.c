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
struct mmc_request {TYPE_1__* cmd; int /*<<< orphan*/  cap_cmd_during_tfr; } ;
struct mmc_host {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmc_complete_cmd (struct mmc_request*) ; 
 int /*<<< orphan*/  mmc_hostname (struct mmc_host*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mmc_command_done(struct mmc_host *host, struct mmc_request *mrq)
{
	if (!mrq->cap_cmd_during_tfr)
		return;

	mmc_complete_cmd(mrq);

	pr_debug("%s: cmd done, tfr ongoing (CMD%u)\n",
		 mmc_hostname(host), mrq->cmd->opcode);
}