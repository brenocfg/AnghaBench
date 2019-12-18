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
struct usdhi6_host {int /*<<< orphan*/  mmc; int /*<<< orphan*/  wait; struct mmc_request* mrq; } ;
struct mmc_request {TYPE_2__* stop; TYPE_1__* cmd; } ;
struct TYPE_4__ {int error; int /*<<< orphan*/  opcode; } ;
struct TYPE_3__ {int opcode; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  MMC_READ_MULTIPLE_BLOCK 129 
 int /*<<< orphan*/  MMC_STOP_TRANSMISSION ; 
#define  MMC_WRITE_MULTIPLE_BLOCK 128 
 int /*<<< orphan*/  USDHI6_WAIT_FOR_STOP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usdhi6_stop_cmd(struct usdhi6_host *host)
{
	struct mmc_request *mrq = host->mrq;

	switch (mrq->cmd->opcode) {
	case MMC_READ_MULTIPLE_BLOCK:
	case MMC_WRITE_MULTIPLE_BLOCK:
		if (mrq->stop->opcode == MMC_STOP_TRANSMISSION) {
			host->wait = USDHI6_WAIT_FOR_STOP;
			return 0;
		}
		/* fall through - Unsupported STOP command. */
	default:
		dev_err(mmc_dev(host->mmc),
			"unsupported stop CMD%d for CMD%d\n",
			mrq->stop->opcode, mrq->cmd->opcode);
		mrq->stop->error = -EOPNOTSUPP;
	}

	return -EOPNOTSUPP;
}