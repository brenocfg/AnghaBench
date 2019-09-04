#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct scatterlist {int dummy; } ;
struct rdma_rw_ctx {scalar_t__ type; TYPE_4__* sig; } ;
struct ib_qp {int /*<<< orphan*/  sig_mrs; TYPE_3__* pd; int /*<<< orphan*/  rdma_mrs; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_6__ {scalar_t__ mr; } ;
struct TYPE_5__ {scalar_t__ mr; } ;
struct TYPE_8__ {scalar_t__ sig_mr; TYPE_2__ prot; TYPE_1__ data; } ;
struct TYPE_7__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 scalar_t__ RDMA_RW_SIG_MR ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  ib_dma_unmap_sg (int /*<<< orphan*/ ,struct scatterlist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ib_mr_pool_put (struct ib_qp*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  kfree (TYPE_4__*) ; 

void rdma_rw_ctx_destroy_signature(struct rdma_rw_ctx *ctx, struct ib_qp *qp,
		u8 port_num, struct scatterlist *sg, u32 sg_cnt,
		struct scatterlist *prot_sg, u32 prot_sg_cnt,
		enum dma_data_direction dir)
{
	if (WARN_ON_ONCE(ctx->type != RDMA_RW_SIG_MR))
		return;

	ib_mr_pool_put(qp, &qp->rdma_mrs, ctx->sig->data.mr);
	ib_dma_unmap_sg(qp->pd->device, sg, sg_cnt, dir);

	if (ctx->sig->prot.mr) {
		ib_mr_pool_put(qp, &qp->rdma_mrs, ctx->sig->prot.mr);
		ib_dma_unmap_sg(qp->pd->device, prot_sg, prot_sg_cnt, dir);
	}

	ib_mr_pool_put(qp, &qp->sig_mrs, ctx->sig->sig_mr);
	kfree(ctx->sig);
}