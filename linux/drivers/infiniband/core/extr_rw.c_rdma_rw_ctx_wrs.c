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
typedef  int /*<<< orphan*/  u8 ;
struct ib_send_wr {int /*<<< orphan*/  send_flags; struct ib_cqe* wr_cqe; struct ib_send_wr* next; int /*<<< orphan*/  opcode; } ;
struct TYPE_12__ {struct ib_send_wr wr; } ;
struct TYPE_13__ {TYPE_5__ wr; } ;
struct TYPE_11__ {TYPE_3__* wrs; } ;
struct rdma_rw_ctx {int type; int nr_ops; TYPE_6__ single; TYPE_4__ map; TYPE_7__* reg; } ;
struct ib_qp {int dummy; } ;
struct ib_cqe {int dummy; } ;
struct TYPE_9__ {struct ib_send_wr wr; } ;
struct TYPE_8__ {struct ib_send_wr wr; } ;
struct TYPE_14__ {TYPE_2__ wr; TYPE_1__ reg_wr; struct ib_send_wr inv_wr; } ;
struct TYPE_10__ {struct ib_send_wr wr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  IB_SEND_SIGNALED ; 
 int /*<<< orphan*/  IB_WR_RDMA_READ_WITH_INV ; 
#define  RDMA_RW_MR 131 
#define  RDMA_RW_MULTI_WR 130 
#define  RDMA_RW_SIG_MR 129 
#define  RDMA_RW_SINGLE_WR 128 
 int /*<<< orphan*/  rdma_rw_update_lkey (TYPE_7__*,int) ; 

struct ib_send_wr *rdma_rw_ctx_wrs(struct rdma_rw_ctx *ctx, struct ib_qp *qp,
		u8 port_num, struct ib_cqe *cqe, struct ib_send_wr *chain_wr)
{
	struct ib_send_wr *first_wr, *last_wr;
	int i;

	switch (ctx->type) {
	case RDMA_RW_SIG_MR:
	case RDMA_RW_MR:
		/* fallthrough */
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