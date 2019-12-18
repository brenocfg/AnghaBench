#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct scatterlist {int dummy; } ;
struct rdma_rw_ctx {int nr_ops; TYPE_7__* reg; int /*<<< orphan*/  type; } ;
struct TYPE_16__ {scalar_t__ sig_type; } ;
struct ib_sig_attrs {TYPE_2__ wire; } ;
struct TYPE_20__ {int num_sge; int /*<<< orphan*/  opcode; TYPE_3__* sg_list; } ;
struct ib_rdma_wr {int rkey; TYPE_6__ wr; int /*<<< orphan*/  remote_addr; } ;
struct ib_qp {int /*<<< orphan*/  sig_mrs; int /*<<< orphan*/  device; int /*<<< orphan*/  integrity_en; TYPE_1__* pd; } ;
struct ib_device {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_22__ {scalar_t__ meta_length; } ;
struct TYPE_18__ {TYPE_6__* next; scalar_t__ send_flags; scalar_t__ num_sge; int /*<<< orphan*/ * wr_cqe; int /*<<< orphan*/  opcode; } ;
struct TYPE_19__ {TYPE_4__ wr; int /*<<< orphan*/  key; TYPE_11__* mr; int /*<<< orphan*/  access; } ;
struct TYPE_17__ {int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;
struct TYPE_21__ {TYPE_11__* mr; TYPE_5__ reg_wr; TYPE_3__ sge; struct ib_rdma_wr wr; } ;
struct TYPE_15__ {struct ib_device* device; } ;
struct TYPE_14__ {TYPE_8__* sig_attrs; int /*<<< orphan*/  length; int /*<<< orphan*/  iova; int /*<<< orphan*/  lkey; } ;

/* Variables and functions */
 int DMA_TO_DEVICE ; 
 int EAGAIN ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IB_ACCESS_LOCAL_WRITE ; 
 int /*<<< orphan*/  IB_ACCESS_REMOTE_WRITE ; 
 scalar_t__ IB_SIG_TYPE_NONE ; 
 int /*<<< orphan*/  IB_WR_RDMA_READ ; 
 int /*<<< orphan*/  IB_WR_RDMA_WRITE ; 
 int /*<<< orphan*/  IB_WR_REG_MR_INTEGRITY ; 
 int /*<<< orphan*/  RDMA_RW_SIG_MR ; 
 int /*<<< orphan*/  SZ_4K ; 
 int ib_dma_map_sg (struct ib_device*,struct scatterlist*,int,int) ; 
 int /*<<< orphan*/  ib_dma_unmap_sg (struct ib_device*,struct scatterlist*,int,int) ; 
 int ib_map_mr_sg_pi (TYPE_11__*,struct scatterlist*,int,int /*<<< orphan*/ *,struct scatterlist*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_11__* ib_mr_pool_get (struct ib_qp*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_mr_pool_put (struct ib_qp*,int /*<<< orphan*/ *,TYPE_11__*) ; 
 TYPE_7__* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_7__*) ; 
 int /*<<< orphan*/  memcpy (TYPE_8__*,struct ib_sig_attrs*,int) ; 
 int /*<<< orphan*/  pr_err (char*,int,...) ; 
 scalar_t__ rdma_protocol_iwarp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rdma_rw_fr_page_list_len (struct ib_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ rdma_rw_inv_key (TYPE_7__*) ; 
 scalar_t__ unlikely (int) ; 

int rdma_rw_ctx_signature_init(struct rdma_rw_ctx *ctx, struct ib_qp *qp,
		u8 port_num, struct scatterlist *sg, u32 sg_cnt,
		struct scatterlist *prot_sg, u32 prot_sg_cnt,
		struct ib_sig_attrs *sig_attrs,
		u64 remote_addr, u32 rkey, enum dma_data_direction dir)
{
	struct ib_device *dev = qp->pd->device;
	u32 pages_per_mr = rdma_rw_fr_page_list_len(qp->pd->device,
						    qp->integrity_en);
	struct ib_rdma_wr *rdma_wr;
	int count = 0, ret;

	if (sg_cnt > pages_per_mr || prot_sg_cnt > pages_per_mr) {
		pr_err("SG count too large: sg_cnt=%d, prot_sg_cnt=%d, pages_per_mr=%d\n",
		       sg_cnt, prot_sg_cnt, pages_per_mr);
		return -EINVAL;
	}

	ret = ib_dma_map_sg(dev, sg, sg_cnt, dir);
	if (!ret)
		return -ENOMEM;
	sg_cnt = ret;

	if (prot_sg_cnt) {
		ret = ib_dma_map_sg(dev, prot_sg, prot_sg_cnt, dir);
		if (!ret) {
			ret = -ENOMEM;
			goto out_unmap_sg;
		}
		prot_sg_cnt = ret;
	}

	ctx->type = RDMA_RW_SIG_MR;
	ctx->nr_ops = 1;
	ctx->reg = kcalloc(1, sizeof(*ctx->reg), GFP_KERNEL);
	if (!ctx->reg) {
		ret = -ENOMEM;
		goto out_unmap_prot_sg;
	}

	ctx->reg->mr = ib_mr_pool_get(qp, &qp->sig_mrs);
	if (!ctx->reg->mr) {
		ret = -EAGAIN;
		goto out_free_ctx;
	}

	count += rdma_rw_inv_key(ctx->reg);

	memcpy(ctx->reg->mr->sig_attrs, sig_attrs, sizeof(struct ib_sig_attrs));

	ret = ib_map_mr_sg_pi(ctx->reg->mr, sg, sg_cnt, NULL, prot_sg,
			      prot_sg_cnt, NULL, SZ_4K);
	if (unlikely(ret)) {
		pr_err("failed to map PI sg (%d)\n", sg_cnt + prot_sg_cnt);
		goto out_destroy_sig_mr;
	}

	ctx->reg->reg_wr.wr.opcode = IB_WR_REG_MR_INTEGRITY;
	ctx->reg->reg_wr.wr.wr_cqe = NULL;
	ctx->reg->reg_wr.wr.num_sge = 0;
	ctx->reg->reg_wr.wr.send_flags = 0;
	ctx->reg->reg_wr.access = IB_ACCESS_LOCAL_WRITE;
	if (rdma_protocol_iwarp(qp->device, port_num))
		ctx->reg->reg_wr.access |= IB_ACCESS_REMOTE_WRITE;
	ctx->reg->reg_wr.mr = ctx->reg->mr;
	ctx->reg->reg_wr.key = ctx->reg->mr->lkey;
	count++;

	ctx->reg->sge.addr = ctx->reg->mr->iova;
	ctx->reg->sge.length = ctx->reg->mr->length;
	if (sig_attrs->wire.sig_type == IB_SIG_TYPE_NONE)
		ctx->reg->sge.length -= ctx->reg->mr->sig_attrs->meta_length;

	rdma_wr = &ctx->reg->wr;
	rdma_wr->wr.sg_list = &ctx->reg->sge;
	rdma_wr->wr.num_sge = 1;
	rdma_wr->remote_addr = remote_addr;
	rdma_wr->rkey = rkey;
	if (dir == DMA_TO_DEVICE)
		rdma_wr->wr.opcode = IB_WR_RDMA_WRITE;
	else
		rdma_wr->wr.opcode = IB_WR_RDMA_READ;
	ctx->reg->reg_wr.wr.next = &rdma_wr->wr;
	count++;

	return count;

out_destroy_sig_mr:
	ib_mr_pool_put(qp, &qp->sig_mrs, ctx->reg->mr);
out_free_ctx:
	kfree(ctx->reg);
out_unmap_prot_sg:
	if (prot_sg_cnt)
		ib_dma_unmap_sg(dev, prot_sg, prot_sg_cnt, dir);
out_unmap_sg:
	ib_dma_unmap_sg(dev, sg, sg_cnt, dir);
	return ret;
}