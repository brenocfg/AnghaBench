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
struct qcom_nand_controller {unsigned int max_cwperpage; int /*<<< orphan*/  dev; } ;
struct bam_transaction {int /*<<< orphan*/  txn_done; void* data_sgl; void* cmd_sgl; void* bam_ce; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int QPIC_PER_CW_CMD_ELEMENTS ; 
 int QPIC_PER_CW_CMD_SGL ; 
 int QPIC_PER_CW_DATA_SGL ; 
 void* devm_kzalloc (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct bam_transaction *
alloc_bam_transaction(struct qcom_nand_controller *nandc)
{
	struct bam_transaction *bam_txn;
	size_t bam_txn_size;
	unsigned int num_cw = nandc->max_cwperpage;
	void *bam_txn_buf;

	bam_txn_size =
		sizeof(*bam_txn) + num_cw *
		((sizeof(*bam_txn->bam_ce) * QPIC_PER_CW_CMD_ELEMENTS) +
		(sizeof(*bam_txn->cmd_sgl) * QPIC_PER_CW_CMD_SGL) +
		(sizeof(*bam_txn->data_sgl) * QPIC_PER_CW_DATA_SGL));

	bam_txn_buf = devm_kzalloc(nandc->dev, bam_txn_size, GFP_KERNEL);
	if (!bam_txn_buf)
		return NULL;

	bam_txn = bam_txn_buf;
	bam_txn_buf += sizeof(*bam_txn);

	bam_txn->bam_ce = bam_txn_buf;
	bam_txn_buf +=
		sizeof(*bam_txn->bam_ce) * QPIC_PER_CW_CMD_ELEMENTS * num_cw;

	bam_txn->cmd_sgl = bam_txn_buf;
	bam_txn_buf +=
		sizeof(*bam_txn->cmd_sgl) * QPIC_PER_CW_CMD_SGL * num_cw;

	bam_txn->data_sgl = bam_txn_buf;

	init_completion(&bam_txn->txn_done);

	return bam_txn;
}