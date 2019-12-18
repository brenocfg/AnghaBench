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
typedef  size_t u64 ;
typedef  size_t u32 ;
struct scatterlist {int dummy; } ;
struct TYPE_6__ {struct ib_sge* sges; struct ib_rdma_wr* wrs; } ;
struct rdma_rw_ctx {size_t nr_ops; TYPE_3__ map; int /*<<< orphan*/  type; } ;
struct ib_sge {size_t addr; size_t length; int /*<<< orphan*/  lkey; } ;
struct TYPE_5__ {size_t num_sge; struct TYPE_5__* next; struct ib_sge* sg_list; int /*<<< orphan*/  opcode; } ;
struct ib_rdma_wr {size_t remote_addr; size_t rkey; TYPE_2__ wr; } ;
struct ib_qp {size_t max_write_sge; size_t max_read_sge; TYPE_1__* pd; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_4__ {int /*<<< orphan*/  local_dma_lkey; } ;

/* Variables and functions */
 size_t DIV_ROUND_UP (size_t,size_t) ; 
 int DMA_TO_DEVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IB_WR_RDMA_READ ; 
 int /*<<< orphan*/  IB_WR_RDMA_WRITE ; 
 int /*<<< orphan*/  RDMA_RW_MULTI_WR ; 
 void* kcalloc (size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ib_sge*) ; 
 size_t min (size_t,size_t) ; 
 size_t sg_dma_address (struct scatterlist*) ; 
 size_t sg_dma_len (struct scatterlist*) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 

__attribute__((used)) static int rdma_rw_init_map_wrs(struct rdma_rw_ctx *ctx, struct ib_qp *qp,
		struct scatterlist *sg, u32 sg_cnt, u32 offset,
		u64 remote_addr, u32 rkey, enum dma_data_direction dir)
{
	u32 max_sge = dir == DMA_TO_DEVICE ? qp->max_write_sge :
		      qp->max_read_sge;
	struct ib_sge *sge;
	u32 total_len = 0, i, j;

	ctx->nr_ops = DIV_ROUND_UP(sg_cnt, max_sge);

	ctx->map.sges = sge = kcalloc(sg_cnt, sizeof(*sge), GFP_KERNEL);
	if (!ctx->map.sges)
		goto out;

	ctx->map.wrs = kcalloc(ctx->nr_ops, sizeof(*ctx->map.wrs), GFP_KERNEL);
	if (!ctx->map.wrs)
		goto out_free_sges;

	for (i = 0; i < ctx->nr_ops; i++) {
		struct ib_rdma_wr *rdma_wr = &ctx->map.wrs[i];
		u32 nr_sge = min(sg_cnt, max_sge);

		if (dir == DMA_TO_DEVICE)
			rdma_wr->wr.opcode = IB_WR_RDMA_WRITE;
		else
			rdma_wr->wr.opcode = IB_WR_RDMA_READ;
		rdma_wr->remote_addr = remote_addr + total_len;
		rdma_wr->rkey = rkey;
		rdma_wr->wr.num_sge = nr_sge;
		rdma_wr->wr.sg_list = sge;

		for (j = 0; j < nr_sge; j++, sg = sg_next(sg)) {
			sge->addr = sg_dma_address(sg) + offset;
			sge->length = sg_dma_len(sg) - offset;
			sge->lkey = qp->pd->local_dma_lkey;

			total_len += sge->length;
			sge++;
			sg_cnt--;
			offset = 0;
		}

		rdma_wr->wr.next = i + 1 < ctx->nr_ops ?
			&ctx->map.wrs[i + 1].wr : NULL;
	}

	ctx->type = RDMA_RW_MULTI_WR;
	return ctx->nr_ops;

out_free_sges:
	kfree(ctx->map.sges);
out:
	return -ENOMEM;
}