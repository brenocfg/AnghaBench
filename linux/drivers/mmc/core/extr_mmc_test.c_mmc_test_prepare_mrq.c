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
struct scatterlist {int dummy; } ;
struct mmc_test_card {int /*<<< orphan*/  card; } ;
struct mmc_request {TYPE_3__* data; TYPE_2__* stop; TYPE_1__* cmd; } ;
struct TYPE_6__ {unsigned int blksz; unsigned int blocks; unsigned int sg_len; struct scatterlist* sg; int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {int flags; scalar_t__ arg; int /*<<< orphan*/  opcode; } ;
struct TYPE_4__ {unsigned int arg; int flags; int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 int MMC_CMD_AC ; 
 int MMC_CMD_ADTC ; 
 int /*<<< orphan*/  MMC_DATA_READ ; 
 int /*<<< orphan*/  MMC_DATA_WRITE ; 
 int /*<<< orphan*/  MMC_READ_MULTIPLE_BLOCK ; 
 int /*<<< orphan*/  MMC_READ_SINGLE_BLOCK ; 
 int MMC_RSP_R1 ; 
 int MMC_RSP_R1B ; 
 int /*<<< orphan*/  MMC_STOP_TRANSMISSION ; 
 int /*<<< orphan*/  MMC_WRITE_BLOCK ; 
 int /*<<< orphan*/  MMC_WRITE_MULTIPLE_BLOCK ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  mmc_card_blockaddr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_set_data_timeout (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_test_prepare_sbc (struct mmc_test_card*,struct mmc_request*,unsigned int) ; 

__attribute__((used)) static void mmc_test_prepare_mrq(struct mmc_test_card *test,
	struct mmc_request *mrq, struct scatterlist *sg, unsigned sg_len,
	unsigned dev_addr, unsigned blocks, unsigned blksz, int write)
{
	if (WARN_ON(!mrq || !mrq->cmd || !mrq->data || !mrq->stop))
		return;

	if (blocks > 1) {
		mrq->cmd->opcode = write ?
			MMC_WRITE_MULTIPLE_BLOCK : MMC_READ_MULTIPLE_BLOCK;
	} else {
		mrq->cmd->opcode = write ?
			MMC_WRITE_BLOCK : MMC_READ_SINGLE_BLOCK;
	}

	mrq->cmd->arg = dev_addr;
	if (!mmc_card_blockaddr(test->card))
		mrq->cmd->arg <<= 9;

	mrq->cmd->flags = MMC_RSP_R1 | MMC_CMD_ADTC;

	if (blocks == 1)
		mrq->stop = NULL;
	else {
		mrq->stop->opcode = MMC_STOP_TRANSMISSION;
		mrq->stop->arg = 0;
		mrq->stop->flags = MMC_RSP_R1B | MMC_CMD_AC;
	}

	mrq->data->blksz = blksz;
	mrq->data->blocks = blocks;
	mrq->data->flags = write ? MMC_DATA_WRITE : MMC_DATA_READ;
	mrq->data->sg = sg;
	mrq->data->sg_len = sg_len;

	mmc_test_prepare_sbc(test, mrq, blocks);

	mmc_set_data_timeout(mrq->data, test->card);
}