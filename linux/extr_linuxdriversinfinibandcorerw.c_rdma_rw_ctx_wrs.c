#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
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
struct ib_send_wr {int /*<<< orphan*/  send_flags; struct ib_cqe* wr_cqe; struct ib_send_wr* next; int /*<<< orphan*/  opcode; } ;
struct TYPE_18__ {struct ib_send_wr wr; } ;
struct TYPE_19__ {TYPE_7__ wr; } ;
struct TYPE_17__ {TYPE_5__* wrs; } ;
struct rdma_rw_ctx {int type; int nr_ops; TYPE_8__ single; TYPE_6__ map; TYPE_9__* reg; TYPE_2__* sig; } ;
struct ib_qp {int dummy; } ;
struct ib_cqe {int dummy; } ;
struct TYPE_15__ {struct ib_send_wr wr; } ;
struct TYPE_14__ {struct ib_send_wr wr; } ;
struct TYPE_20__ {TYPE_4__ wr; TYPE_3__ reg_wr; struct ib_send_wr inv_wr; int /*<<< orphan*/  mr; } ;
struct TYPE_16__ {struct ib_send_wr wr; } ;
struct TYPE_12__ {int /*<<< orphan*/  lkey; } ;
struct TYPE_13__ {TYPE_9__ data; TYPE_10__* sig_mr; TYPE_1__ sig_sge; TYPE_9__ prot; } ;
struct TYPE_11__ {int need_inval; int /*<<< orphan*/  lkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  IB_SEND_SIGNALED ; 
 int /*<<< orphan*/  IB_WR_RDMA_READ_WITH_INV ; 
#define  RDMA_RW_MR 131 
#define  RDMA_RW_MULTI_WR 130 
#define  RDMA_RW_SIG_MR 129 
#define  RDMA_RW_SINGLE_WR 128 
 int /*<<< orphan*/  ib_inc_rkey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_update_fast_reg_key (TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_rw_update_lkey (TYPE_9__*,int) ; 

struct ib_send_wr *rdma_rw_ctx_wrs(struct rdma_rw_ctx *ctx, struct ib_qp *qp,
		u8 port_num, struct ib_cqe *cqe, struct ib_send_wr *chain_wr)
{
	struct ib_send_wr *first_wr, *last_wr;
	int i;

	switch (ctx->type) {
	case RDMA_RW_SIG_MR:
		rdma_rw_update_lkey(&ctx->sig->data, true);
		if (ctx->sig->prot.mr)
			rdma_rw_update_lkey(&ctx->sig->prot, true);
	
		ctx->sig->sig_mr->need_inval = true;
		ib_update_fast_reg_key(ctx->sig->sig_mr,
			ib_inc_rkey(ctx->sig->sig_mr->lkey));
		ctx->sig->sig_sge.lkey = ctx->sig->sig_mr->lkey;

		if (ctx->sig->data.inv_wr.next)
			first_wr = &ctx->sig->data.inv_wr;
		else
			first_wr = &ctx->sig->data.reg_wr.wr;
		last_wr = &ctx->sig->data.wr.wr;
		break;
	case RDMA_RW_MR:
		for (i = 0; i < ctx->nr_ops; i++) {
			rdma_rw_update_lkey(&ctx->reg[i],
				ctx->reg[i].wr.wr.opcode !=
					IB_WR_RDMA_READ_WITH_INV);
		}

		if (ctx->reg[0].inv_wr.next)
			first_wr = &ctx->reg[0].inv_wr;
		else
			first_wr = &ctx->reg[0].reg_wr.wr;
		last_wr = &ctx->reg[ctx->nr_ops - 1].wr.wr;
		break;
	case RDMA_RW_MULTI_WR:
		first_wr = &ctx->map.wrs[0].wr;
		last_wr = &ctx->map.wrs[ctx->nr_ops - 1].wr;
		break;
	case RDMA_RW_SINGLE_WR:
		first_wr = &ctx->single.wr.wr;
		last_wr = &ctx->single.wr.wr;
		break;
	default:
		BUG();
	}

	if (chain_wr) {
		last_wr->next = chain_wr;
	} else {
		last_wr->wr_cqe = cqe;
		last_wr->send_flags |= IB_SEND_SIGNALED;
	}

	return first_wr;
}