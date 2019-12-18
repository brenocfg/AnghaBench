#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct scatterlist {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  invalidate_rkey; } ;
struct TYPE_14__ {int num_sge; TYPE_5__* next; TYPE_3__ ex; int /*<<< orphan*/  opcode; TYPE_4__* sg_list; } ;
struct TYPE_15__ {int rkey; TYPE_6__ wr; int /*<<< orphan*/  remote_addr; } ;
struct TYPE_12__ {scalar_t__ length; } ;
struct TYPE_13__ {TYPE_6__* next; } ;
struct TYPE_10__ {TYPE_5__ wr; } ;
struct rdma_rw_reg_ctx {TYPE_8__* mr; TYPE_7__ wr; TYPE_4__ sge; TYPE_2__ reg_wr; TYPE_5__ inv_wr; } ;
struct rdma_rw_ctx {int nr_ops; struct rdma_rw_reg_ctx* reg; int /*<<< orphan*/  type; } ;
struct ib_qp {int /*<<< orphan*/  rdma_mrs; int /*<<< orphan*/  device; int /*<<< orphan*/  integrity_en; TYPE_1__* pd; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_16__ {int /*<<< orphan*/  lkey; scalar_t__ need_inval; } ;
struct TYPE_9__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int DMA_TO_DEVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IB_WR_RDMA_READ ; 
 int /*<<< orphan*/  IB_WR_RDMA_READ_WITH_INV ; 
 int /*<<< orphan*/  IB_WR_RDMA_WRITE ; 
 int /*<<< orphan*/  RDMA_RW_MR ; 
 int /*<<< orphan*/  ib_mr_pool_put (struct ib_qp*,int /*<<< orphan*/ *,TYPE_8__*) ; 
 struct rdma_rw_reg_ctx* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct rdma_rw_reg_ctx*) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  rdma_cap_read_inv (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rdma_rw_fr_page_list_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rdma_rw_init_one_mr (struct ib_qp*,int /*<<< orphan*/ ,struct rdma_rw_reg_ctx*,struct scatterlist*,int,int) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 

__attribute__((used)) static int rdma_rw_init_mr_wrs(struct rdma_rw_ctx *ctx, struct ib_qp *qp,
		u8 port_num, struct scatterlist *sg, u32 sg_cnt, u32 offset,
		u64 remote_addr, u32 rkey, enum dma_data_direction dir)
{
	struct rdma_rw_reg_ctx *prev = NULL;
	u32 pages_per_mr = rdma_rw_fr_page_list_len(qp->pd->device,
						    qp->integrity_en);
	int i, j, ret = 0, count = 0;

	ctx->nr_ops = (sg_cnt + pages_per_mr - 1) / pages_per_mr;
	ctx->reg = kcalloc(ctx->nr_ops, sizeof(*ctx->reg), GFP_KERNEL);
	if (!ctx->reg) {
		ret = -ENOMEM;
		goto out;
	}

	for (i = 0; i < ctx->nr_ops; i++) {
		struct rdma_rw_reg_ctx *reg = &ctx->reg[i];
		u32 nents = min(sg_cnt, pages_per_mr);

		ret = rdma_rw_init_one_mr(qp, port_num, reg, sg, sg_cnt,
				offset);
		if (ret < 0)
			goto out_free;
		count += ret;

		if (prev) {
			if (reg->mr->need_inval)
				prev->wr.wr.next = &reg->inv_wr;
			else
				prev->wr.wr.next = &reg->reg_wr.wr;
		}

		reg->reg_wr.wr.next = &reg->wr.wr;

		reg->wr.wr.sg_list = &reg->sge;
		reg->wr.wr.num_sge = 1;
		reg->wr.remote_addr = remote_addr;
		reg->wr.rkey = rkey;
		if (dir == DMA_TO_DEVICE) {
			reg->wr.wr.opcode = IB_WR_RDMA_WRITE;
		} else if (!rdma_cap_read_inv(qp->device, port_num)) {
			reg->wr.wr.opcode = IB_WR_RDMA_READ;
		} else {
			reg->wr.wr.opcode = IB_WR_RDMA_READ_WITH_INV;
			reg->wr.wr.ex.invalidate_rkey = reg->mr->lkey;
		}
		count++;

		remote_addr += reg->sge.length;
		sg_cnt -= nents;
		for (j = 0; j < nents; j++)
			sg = sg_next(sg);
		prev = reg;
		offset = 0;
	}

	if (prev)
		prev->wr.wr.next = NULL;

	ctx->type = RDMA_RW_MR;
	return count;

out_free:
	while (--i >= 0)
		ib_mr_pool_put(qp, &qp->rdma_mrs, ctx->reg[i].mr);
	kfree(ctx->reg);
out:
	return ret;
}