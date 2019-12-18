#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct request {int /*<<< orphan*/  q; } ;
struct TYPE_5__ {int /*<<< orphan*/  sgl; } ;
struct nvmefc_fcp_req {scalar_t__ sg_cnt; TYPE_2__ sg_table; int /*<<< orphan*/  first_sgl; } ;
struct nvme_fc_fcp_op {int /*<<< orphan*/  nents; struct nvmefc_fcp_req fcp_req; } ;
struct nvme_fc_ctrl {TYPE_1__* lport; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  SG_CHUNK_SIZE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  blk_rq_map_sg (int /*<<< orphan*/ ,struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_rq_nr_phys_segments (struct request*) ; 
 scalar_t__ fc_dma_map_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rq_dma_dir (struct request*) ; 
 int sg_alloc_table_chained (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_free_table_chained (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
nvme_fc_map_data(struct nvme_fc_ctrl *ctrl, struct request *rq,
		struct nvme_fc_fcp_op *op)
{
	struct nvmefc_fcp_req *freq = &op->fcp_req;
	int ret;

	freq->sg_cnt = 0;

	if (!blk_rq_nr_phys_segments(rq))
		return 0;

	freq->sg_table.sgl = freq->first_sgl;
	ret = sg_alloc_table_chained(&freq->sg_table,
			blk_rq_nr_phys_segments(rq), freq->sg_table.sgl,
			SG_CHUNK_SIZE);
	if (ret)
		return -ENOMEM;

	op->nents = blk_rq_map_sg(rq->q, rq, freq->sg_table.sgl);
	WARN_ON(op->nents > blk_rq_nr_phys_segments(rq));
	freq->sg_cnt = fc_dma_map_sg(ctrl->lport->dev, freq->sg_table.sgl,
				op->nents, rq_dma_dir(rq));
	if (unlikely(freq->sg_cnt <= 0)) {
		sg_free_table_chained(&freq->sg_table, SG_CHUNK_SIZE);
		freq->sg_cnt = 0;
		return -EFAULT;
	}

	/*
	 * TODO: blk_integrity_rq(rq)  for DIF
	 */
	return 0;
}