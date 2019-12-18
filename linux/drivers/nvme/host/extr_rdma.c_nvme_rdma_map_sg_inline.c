#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct scatterlist {int dummy; } ;
struct nvme_sgl_desc {int type; int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;
struct TYPE_10__ {struct scatterlist* sgl; } ;
struct nvme_rdma_request {int num_sge; struct ib_sge* sge; TYPE_3__ sg_table; } ;
struct nvme_rdma_queue {TYPE_7__* ctrl; TYPE_5__* device; } ;
struct TYPE_8__ {struct nvme_sgl_desc sgl; } ;
struct TYPE_9__ {TYPE_1__ dptr; } ;
struct nvme_command {TYPE_2__ common; } ;
struct ib_sge {scalar_t__ length; int /*<<< orphan*/  lkey; int /*<<< orphan*/  addr; } ;
struct TYPE_13__ {int /*<<< orphan*/  icdoff; } ;
struct TYPE_14__ {TYPE_6__ ctrl; } ;
struct TYPE_12__ {TYPE_4__* pd; } ;
struct TYPE_11__ {int /*<<< orphan*/  local_dma_lkey; } ;

/* Variables and functions */
 int NVME_SGL_FMT_DATA_DESC ; 
 int NVME_SGL_FMT_OFFSET ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_dma_address (struct scatterlist*) ; 
 scalar_t__ sg_dma_len (struct scatterlist*) ; 

__attribute__((used)) static int nvme_rdma_map_sg_inline(struct nvme_rdma_queue *queue,
		struct nvme_rdma_request *req, struct nvme_command *c,
		int count)
{
	struct nvme_sgl_desc *sg = &c->common.dptr.sgl;
	struct scatterlist *sgl = req->sg_table.sgl;
	struct ib_sge *sge = &req->sge[1];
	u32 len = 0;
	int i;

	for (i = 0; i < count; i++, sgl++, sge++) {
		sge->addr = sg_dma_address(sgl);
		sge->length = sg_dma_len(sgl);
		sge->lkey = queue->device->pd->local_dma_lkey;
		len += sge->length;
	}

	sg->addr = cpu_to_le64(queue->ctrl->ctrl.icdoff);
	sg->length = cpu_to_le32(len);
	sg->type = (NVME_SGL_FMT_DATA_DESC << 4) | NVME_SGL_FMT_OFFSET;

	req->num_sge += count;
	return 0;
}