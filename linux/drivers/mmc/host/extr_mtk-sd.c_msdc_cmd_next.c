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
struct msdc_host {int dummy; } ;
struct mmc_request {int /*<<< orphan*/  cmd; struct mmc_command* sbc; } ;
struct mmc_command {scalar_t__ opcode; int /*<<< orphan*/  data; scalar_t__ error; } ;

/* Variables and functions */
 scalar_t__ EILSEQ ; 
 scalar_t__ MMC_SEND_TUNING_BLOCK ; 
 scalar_t__ MMC_SEND_TUNING_BLOCK_HS200 ; 
 int /*<<< orphan*/  msdc_request_done (struct msdc_host*,struct mmc_request*) ; 
 int /*<<< orphan*/  msdc_start_command (struct msdc_host*,struct mmc_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msdc_start_data (struct msdc_host*,struct mmc_request*,struct mmc_command*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void msdc_cmd_next(struct msdc_host *host,
		struct mmc_request *mrq, struct mmc_command *cmd)
{
	if ((cmd->error &&
	    !(cmd->error == -EILSEQ &&
	      (cmd->opcode == MMC_SEND_TUNING_BLOCK ||
	       cmd->opcode == MMC_SEND_TUNING_BLOCK_HS200))) ||
	    (mrq->sbc && mrq->sbc->error))
		msdc_request_done(host, mrq);
	else if (cmd == mrq->sbc)
		msdc_start_command(host, mrq, mrq->cmd);
	else if (!cmd->data)
		msdc_request_done(host, mrq);
	else
		msdc_start_data(host, mrq, cmd, cmd->data);
}