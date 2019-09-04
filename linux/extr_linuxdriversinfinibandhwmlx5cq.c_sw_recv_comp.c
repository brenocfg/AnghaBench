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
struct mlx5_ib_wq {unsigned int head; int tail; int wqe_cnt; int /*<<< orphan*/ * wrid; } ;
struct mlx5_ib_qp {int /*<<< orphan*/  ibqp; struct mlx5_ib_wq rq; } ;
struct ib_wc {int /*<<< orphan*/ * qp; int /*<<< orphan*/  vendor_err; int /*<<< orphan*/  status; int /*<<< orphan*/  wr_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_WC_WR_FLUSH_ERR ; 
 int /*<<< orphan*/  MLX5_CQE_SYNDROME_WR_FLUSH_ERR ; 

__attribute__((used)) static void sw_recv_comp(struct mlx5_ib_qp *qp, int num_entries,
			 struct ib_wc *wc, int *npolled)
{
	struct mlx5_ib_wq *wq;
	unsigned int cur;
	int np;
	int i;

	wq = &qp->rq;
	cur = wq->head - wq->tail;
	np = *npolled;

	if (cur == 0)
		return;

	for (i = 0;  i < cur && np < num_entries; i++) {
		wc->wr_id = wq->wrid[wq->tail & (wq->wqe_cnt - 1)];
		wc->status = IB_WC_WR_FLUSH_ERR;
		wc->vendor_err = MLX5_CQE_SYNDROME_WR_FLUSH_ERR;
		wq->tail++;
		np++;
		wc->qp = &qp->ibqp;
		wc++;
	}
	*npolled = np;
}