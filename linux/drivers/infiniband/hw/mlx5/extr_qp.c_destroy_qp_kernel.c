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
struct TYPE_4__ {int /*<<< orphan*/  wrid; } ;
struct TYPE_3__ {int /*<<< orphan*/  wr_data; int /*<<< orphan*/  wrid; int /*<<< orphan*/  w_list; int /*<<< orphan*/  wqe_head; } ;
struct mlx5_ib_qp {int /*<<< orphan*/  buf; int /*<<< orphan*/  db; TYPE_2__ rq; TYPE_1__ sq; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_db_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_frag_buf_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void destroy_qp_kernel(struct mlx5_ib_dev *dev, struct mlx5_ib_qp *qp)
{
	kvfree(qp->sq.wqe_head);
	kvfree(qp->sq.w_list);
	kvfree(qp->sq.wrid);
	kvfree(qp->sq.wr_data);
	kvfree(qp->rq.wrid);
	mlx5_db_free(dev->mdev, &qp->db);
	mlx5_frag_buf_free(dev->mdev, &qp->buf);
}