#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct msdc_host {int dummy; } ;
struct mmc_request {TYPE_2__* stop; int /*<<< orphan*/  sbc; TYPE_1__* cmd; } ;
struct mmc_data {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  error; } ;
struct TYPE_3__ {int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 scalar_t__ mmc_op_multi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msdc_request_done (struct msdc_host*,struct mmc_request*) ; 
 int /*<<< orphan*/  msdc_start_command (struct msdc_host*,struct mmc_request*,TYPE_2__*) ; 

__attribute__((used)) static void msdc_data_xfer_next(struct msdc_host *host,
				struct mmc_request *mrq, struct mmc_data *data)
{
	if (mmc_op_multi(mrq->cmd->opcode) && mrq->stop && !mrq->stop->error &&
	    !mrq->sbc)
		msdc_start_command(host, mrq, mrq->stop);
	else
		msdc_request_done(host, mrq);
}