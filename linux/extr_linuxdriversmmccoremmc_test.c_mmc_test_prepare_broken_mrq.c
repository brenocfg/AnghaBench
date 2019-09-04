#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mmc_test_card {TYPE_1__* card; } ;
struct mmc_request {TYPE_2__* cmd; int /*<<< orphan*/ * stop; TYPE_3__* data; } ;
struct TYPE_6__ {int blocks; } ;
struct TYPE_5__ {int arg; int /*<<< orphan*/  opcode; } ;
struct TYPE_4__ {int rca; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMC_READ_SINGLE_BLOCK ; 
 int /*<<< orphan*/  MMC_SEND_STATUS ; 
 int /*<<< orphan*/  MMC_WRITE_BLOCK ; 
 scalar_t__ WARN_ON (int) ; 

__attribute__((used)) static void mmc_test_prepare_broken_mrq(struct mmc_test_card *test,
	struct mmc_request *mrq, int write)
{
	if (WARN_ON(!mrq || !mrq->cmd || !mrq->data))
		return;

	if (mrq->data->blocks > 1) {
		mrq->cmd->opcode = write ?
			MMC_WRITE_BLOCK : MMC_READ_SINGLE_BLOCK;
		mrq->stop = NULL;
	} else {
		mrq->cmd->opcode = MMC_SEND_STATUS;
		mrq->cmd->arg = test->card->rca << 16;
	}
}