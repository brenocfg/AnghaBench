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
struct qcom_nand_controller {int max_cwperpage; TYPE_1__* props; struct bam_transaction* bam_txn; } ;
struct bam_transaction {int wait_second_completion; int /*<<< orphan*/  txn_done; int /*<<< orphan*/  data_sgl; int /*<<< orphan*/  cmd_sgl; int /*<<< orphan*/ * last_data_desc; scalar_t__ rx_sgl_start; scalar_t__ rx_sgl_pos; scalar_t__ tx_sgl_start; scalar_t__ tx_sgl_pos; scalar_t__ cmd_sgl_start; scalar_t__ cmd_sgl_pos; scalar_t__ bam_ce_start; scalar_t__ bam_ce_pos; } ;
struct TYPE_2__ {int /*<<< orphan*/  is_bam; } ;

/* Variables and functions */
 int QPIC_PER_CW_CMD_SGL ; 
 int QPIC_PER_CW_DATA_SGL ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sg_init_table (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void clear_bam_transaction(struct qcom_nand_controller *nandc)
{
	struct bam_transaction *bam_txn = nandc->bam_txn;

	if (!nandc->props->is_bam)
		return;

	bam_txn->bam_ce_pos = 0;
	bam_txn->bam_ce_start = 0;
	bam_txn->cmd_sgl_pos = 0;
	bam_txn->cmd_sgl_start = 0;
	bam_txn->tx_sgl_pos = 0;
	bam_txn->tx_sgl_start = 0;
	bam_txn->rx_sgl_pos = 0;
	bam_txn->rx_sgl_start = 0;
	bam_txn->last_data_desc = NULL;
	bam_txn->wait_second_completion = false;

	sg_init_table(bam_txn->cmd_sgl, nandc->max_cwperpage *
		      QPIC_PER_CW_CMD_SGL);
	sg_init_table(bam_txn->data_sgl, nandc->max_cwperpage *
		      QPIC_PER_CW_DATA_SGL);

	reinit_completion(&bam_txn->txn_done);
}