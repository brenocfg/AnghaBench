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
struct mmc_test_card {struct mmc_card* card; } ;
struct mmc_request {TYPE_2__* sbc; TYPE_1__* cmd; } ;
struct mmc_card {int quirks; int /*<<< orphan*/  host; } ;
struct TYPE_4__ {unsigned int arg; int flags; int /*<<< orphan*/  opcode; } ;
struct TYPE_3__ {int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 int MMC_CMD_AC ; 
 int MMC_QUIRK_BLK_NO_CMD23 ; 
 int MMC_RSP_R1 ; 
 int /*<<< orphan*/  MMC_SET_BLOCK_COUNT ; 
 int /*<<< orphan*/  mmc_host_cmd23 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_op_multi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_test_card_cmd23 (struct mmc_card*) ; 

__attribute__((used)) static void mmc_test_prepare_sbc(struct mmc_test_card *test,
				 struct mmc_request *mrq, unsigned int blocks)
{
	struct mmc_card *card = test->card;

	if (!mrq->sbc || !mmc_host_cmd23(card->host) ||
	    !mmc_test_card_cmd23(card) || !mmc_op_multi(mrq->cmd->opcode) ||
	    (card->quirks & MMC_QUIRK_BLK_NO_CMD23)) {
		mrq->sbc = NULL;
		return;
	}

	mrq->sbc->opcode = MMC_SET_BLOCK_COUNT;
	mrq->sbc->arg = blocks;
	mrq->sbc->flags = MMC_RSP_R1 | MMC_CMD_AC;
}