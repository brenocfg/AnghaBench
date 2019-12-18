#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mlx5_ib_wq {int /*<<< orphan*/  wqe_shift; int /*<<< orphan*/  wqe_cnt; int /*<<< orphan*/  offset; } ;
struct TYPE_4__ {struct ib_umem* umem; } ;
struct mlx5_ib_qp_base {TYPE_2__ ubuffer; } ;
struct TYPE_3__ {struct mlx5_ib_qp_base base; } ;
struct mlx5_ib_qp {struct mlx5_ib_wq rq; TYPE_1__ trans_qp; } ;
struct ib_umem {int dummy; } ;

/* Variables and functions */
 int mlx5_ib_read_user_wqe_common (struct ib_umem*,void*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,size_t*) ; 

int mlx5_ib_read_user_wqe_rq(struct mlx5_ib_qp *qp,
			     int wqe_index,
			     void *buffer,
			     int buflen,
			     size_t *bc)
{
	struct mlx5_ib_qp_base *base = &qp->trans_qp.base;
	struct ib_umem *umem = base->ubuffer.umem;
	struct mlx5_ib_wq *wq = &qp->rq;
	size_t bytes_copied;
	int ret;

	ret = mlx5_ib_read_user_wqe_common(umem,
					   buffer,
					   buflen,
					   wqe_index,
					   wq->offset,
					   wq->wqe_cnt,
					   wq->wqe_shift,
					   buflen,
					   &bytes_copied);

	if (ret)
		return ret;
	*bc = bytes_copied;
	return 0;
}