#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct scatterlist {int dummy; } ;
struct rdma_rw_ctx {int nr_ops; TYPE_8__* sig; int /*<<< orphan*/  type; } ;
struct TYPE_13__ {scalar_t__ sig_type; } ;
struct ib_sig_attrs {TYPE_2__ wire; } ;
struct TYPE_17__ {int /*<<< orphan*/  invalidate_rkey; } ;
struct ib_send_wr {int num_sge; struct ib_send_wr* next; int /*<<< orphan*/  opcode; TYPE_3__* sg_list; int /*<<< orphan*/ * wr_cqe; TYPE_6__ ex; } ;
struct ib_rdma_wr {int rkey; struct ib_send_wr wr; int /*<<< orphan*/  remote_addr; } ;
struct ib_qp {int /*<<< orphan*/  rdma_mrs; int /*<<< orphan*/  sig_mrs; TYPE_4__* pd; } ;
struct ib_device {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_14__ {scalar_t__ length; scalar_t__ addr; } ;
struct TYPE_16__ {struct ib_send_wr wr; } ;
struct TYPE_18__ {int /*<<< orphan*/  mr; struct ib_rdma_wr wr; TYPE_3__ sge; TYPE_5__ reg_wr; struct ib_send_wr inv_wr; } ;
struct TYPE_12__ {struct ib_send_wr wr; TYPE_3__* prot; TYPE_10__* sig_mr; struct ib_sig_attrs* sig_attrs; int /*<<< orphan*/  access_flags; } ;
struct TYPE_19__ {TYPE_7__ data; TYPE_7__ prot; TYPE_3__ sig_sge; TYPE_1__ sig_wr; TYPE_10__* sig_mr; struct ib_send_wr sig_inv_wr; } ;
struct TYPE_15__ {struct ib_device* device; } ;
struct TYPE_11__ {int /*<<< orphan*/  rkey; scalar_t__ need_inval; } ;

/* Variables and functions */
 int DMA_TO_DEVICE ; 
 int EAGAIN ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IB_ACCESS_LOCAL_WRITE ; 
 scalar_t__ IB_SIG_TYPE_NONE ; 
 int /*<<< orphan*/  IB_WR_LOCAL_INV ; 
 int /*<<< orphan*/  IB_WR_RDMA_READ ; 
 int /*<<< orphan*/  IB_WR_RDMA_WRITE ; 
 int /*<<< orphan*/  IB_WR_REG_SIG_MR ; 
 int /*<<< orphan*/  RDMA_RW_SIG_MR ; 
 int ib_dma_map_sg (struct ib_device*,struct scatterlist*,int,int) ; 
 int /*<<< orphan*/  ib_dma_unmap_sg (struct ib_device*,struct scatterlist*,int,int) ; 
 TYPE_10__* ib_mr_pool_get (struct ib_qp*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_mr_pool_put (struct ib_qp*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_8__* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_8__*) ; 
 int /*<<< orphan*/  memset (struct ib_send_wr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int rdma_rw_fr_page_list_len (struct ib_device*) ; 
 int rdma_rw_init_one_mr (struct ib_qp*,int /*<<< orphan*/ ,TYPE_7__*,struct scatterlist*,int,int /*<<< orphan*/ ) ; 

int rdma_rw_ctx_signature_init(struct rdma_rw_ctx *ctx, struct ib_qp *qp,
		u8 port_num, struct scatterlist *sg, u32 sg_cnt,
		struct scatterlist *prot_sg, u32 prot_sg_cnt,
		struct ib_sig_attrs *sig_attrs,
		u64 remote_addr, u32 rkey, enum dma_data_direction dir)
{
	struct ib_device *dev = qp->pd->device;
	u32 pages_per_mr = rdma_rw_fr_page_list_len(qp->pd->device);
	struct ib_rdma_wr *rdma_wr;
	struct ib_send_wr *prev_wr = NULL;
	int count = 0, ret;

	if (sg_cnt > pages_per_mr || prot_sg_cnt > pages_per_mr) {
		pr_err("SG count too large\n");
		return -EINVAL;
	}

	ret = ib_dma_map_sg(dev, sg, sg_cnt, dir);
	if (!ret)
		return -ENOMEM;
	sg_cnt = ret;

	ret = ib_dma_map_sg(dev, prot_sg, prot_sg_cnt, dir);
	if (!ret) {
		ret = -ENOMEM;
		goto out_unmap_sg;
	}
	prot_sg_cnt = ret;

	ctx->type = RDMA_RW_SIG_MR;
	ctx->nr_ops = 1;
	ctx->sig = kcalloc(1, sizeof(*ctx->sig), GFP_KERNEL);
	if (!ctx->sig) {
		ret = -ENOMEM;
		goto out_unmap_prot_sg;
	}

	ret = rdma_rw_init_one_mr(qp, port_num, &ctx->sig->data, sg, sg_cnt, 0);
	if (ret < 0)
		goto out_free_ctx;
	count += ret;
	prev_wr = &ctx->sig->data.reg_wr.wr;

	ret = rdma_rw_init_one_mr(qp, port_num, &ctx->sig->prot,
				  prot_sg, prot_sg_cnt, 0);
	if (ret < 0)
		goto out_destroy_data_mr;
	count += ret;

	if (ctx->sig->prot.inv_wr.next)
		prev_wr->next = &ctx->sig->prot.inv_wr;
	else
		prev_wr->next = &ctx->sig->prot.reg_wr.wr;
	prev_wr = &ctx->sig->prot.reg_wr.wr;

	ctx->sig->sig_mr = ib_mr_pool_get(qp, &qp->sig_mrs);
	if (!ctx->sig->sig_mr) {
		ret = -EAGAIN;
		goto out_destroy_prot_mr;
	}

	if (ctx->sig->sig_mr->need_inval) {
		memset(&ctx->sig->sig_inv_wr, 0, sizeof(ctx->sig->sig_inv_wr));

		ctx->sig->sig_inv_wr.opcode = IB_WR_LOCAL_INV;
		ctx->sig->sig_inv_wr.ex.invalidate_rkey = ctx->sig->sig_mr->rkey;

		prev_wr->next = &ctx->sig->sig_inv_wr;
		prev_wr = &ctx->sig->sig_inv_wr;
	}

	ctx->sig->sig_wr.wr.opcode = IB_WR_REG_SIG_MR;
	ctx->sig->sig_wr.wr.wr_cqe = NULL;
	ctx->sig->sig_wr.wr.sg_list = &ctx->sig->data.sge;
	ctx->sig->sig_wr.wr.num_sge = 1;
	ctx->sig->sig_wr.access_flags = IB_ACCESS_LOCAL_WRITE;
	ctx->sig->sig_wr.sig_attrs = sig_attrs;
	ctx->sig->sig_wr.sig_mr = ctx->sig->sig_mr;
	if (prot_sg_cnt)
		ctx->sig->sig_wr.prot = &ctx->sig->prot.sge;
	prev_wr->next = &ctx->sig->sig_wr.wr;
	prev_wr = &ctx->sig->sig_wr.wr;
	count++;

	ctx->sig->sig_sge.addr = 0;
	ctx->sig->sig_sge.length = ctx->sig->data.sge.length;
	if (sig_attrs->wire.sig_type != IB_SIG_TYPE_NONE)
		ctx->sig->sig_sge.length += ctx->sig->prot.sge.length;

	rdma_wr = &ctx->sig->data.wr;
	rdma_wr->wr.sg_list = &ctx->sig->sig_sge;
	rdma_wr->wr.num_sge = 1;
	rdma_wr->remote_addr = remote_addr;
	rdma_wr->rkey = rkey;
	if (dir == DMA_TO_DEVICE)
		rdma_wr->wr.opcode = IB_WR_RDMA_WRITE;
	else
		rdma_wr->wr.opcode = IB_WR_RDMA_READ;
	prev_wr->next = &rdma_wr->wr;
	prev_wr = &rdma_wr->wr;
	count++;

	return count;

out_destroy_prot_mr:
	if (prot_sg_cnt)
		ib_mr_pool_put(qp, &qp->rdma_mrs, ctx->sig->prot.mr);
out_destroy_data_mr:
	ib_mr_pool_put(qp, &qp->rdma_mrs, ctx->sig->data.mr);
out_free_ctx:
	kfree(ctx->sig);
out_unmap_prot_sg:
	ib_dma_unmap_sg(dev, prot_sg, prot_sg_cnt, dir);
out_unmap_sg:
	ib_dma_unmap_sg(dev, sg, sg_cnt, dir);
	return ret;
}