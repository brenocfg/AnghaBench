#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct rdma_rw_ctx {int dummy; } ;
struct ib_send_wr {int dummy; } ;
struct ib_qp {int dummy; } ;
struct ib_cqe {int dummy; } ;

/* Variables and functions */
 int ib_post_send (struct ib_qp*,struct ib_send_wr*,int /*<<< orphan*/ *) ; 
 struct ib_send_wr* rdma_rw_ctx_wrs (struct rdma_rw_ctx*,struct ib_qp*,int /*<<< orphan*/ ,struct ib_cqe*,struct ib_send_wr*) ; 

int rdma_rw_ctx_post(struct rdma_rw_ctx *ctx, struct ib_qp *qp, u8 port_num,
		struct ib_cqe *cqe, struct ib_send_wr *chain_wr)
{
	struct ib_send_wr *first_wr;

	first_wr = rdma_rw_ctx_wrs(ctx, qp, port_num, cqe, chain_wr);
	return ib_post_send(qp, first_wr, NULL);
}