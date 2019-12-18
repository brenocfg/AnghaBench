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
struct mlx4_ib_qp {scalar_t__ counter_index; } ;
struct mlx4_ib_dev {int dummy; } ;
struct ib_wq {int /*<<< orphan*/  device; } ;
struct ib_udata {int dummy; } ;
struct ib_qp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX4_IB_RWQ_SRC ; 
 int /*<<< orphan*/  destroy_qp_common (struct mlx4_ib_dev*,struct mlx4_ib_qp*,int /*<<< orphan*/ ,struct ib_udata*) ; 
 int /*<<< orphan*/  kfree (struct mlx4_ib_qp*) ; 
 int /*<<< orphan*/  mlx4_ib_free_qp_counter (struct mlx4_ib_dev*,struct mlx4_ib_qp*) ; 
 struct mlx4_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 
 struct mlx4_ib_qp* to_mqp (struct ib_qp*) ; 

void mlx4_ib_destroy_wq(struct ib_wq *ibwq, struct ib_udata *udata)
{
	struct mlx4_ib_dev *dev = to_mdev(ibwq->device);
	struct mlx4_ib_qp *qp = to_mqp((struct ib_qp *)ibwq);

	if (qp->counter_index)
		mlx4_ib_free_qp_counter(dev, qp);

	destroy_qp_common(dev, qp, MLX4_IB_RWQ_SRC, udata);

	kfree(qp);
}