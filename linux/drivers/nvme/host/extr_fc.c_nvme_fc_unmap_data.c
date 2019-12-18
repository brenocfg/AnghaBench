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
struct request {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  sgl; } ;
struct nvmefc_fcp_req {scalar_t__ sg_cnt; TYPE_2__ sg_table; } ;
struct nvme_fc_fcp_op {int /*<<< orphan*/  nents; struct nvmefc_fcp_req fcp_req; } ;
struct nvme_fc_ctrl {TYPE_1__* lport; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SG_CHUNK_SIZE ; 
 int /*<<< orphan*/  fc_dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_cleanup_cmd (struct request*) ; 
 int /*<<< orphan*/  rq_dma_dir (struct request*) ; 
 int /*<<< orphan*/  sg_free_table_chained (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nvme_fc_unmap_data(struct nvme_fc_ctrl *ctrl, struct request *rq,
		struct nvme_fc_fcp_op *op)
{
	struct nvmefc_fcp_req *freq = &op->fcp_req;

	if (!freq->sg_cnt)
		return;

	fc_dma_unmap_sg(ctrl->lport->dev, freq->sg_table.sgl, op->nents,
			rq_dma_dir(rq));

	nvme_cleanup_cmd(rq);

	sg_free_table_chained(&freq->sg_table, SG_CHUNK_SIZE);

	freq->sg_cnt = 0;
}