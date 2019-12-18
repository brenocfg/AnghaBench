#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct umr_common {int /*<<< orphan*/  sem; int /*<<< orphan*/  qp; } ;
struct TYPE_2__ {int /*<<< orphan*/ * wr_cqe; } ;
struct mlx5_umr_wr {TYPE_1__ wr; } ;
struct mlx5_ib_umr_context {int status; int /*<<< orphan*/  done; int /*<<< orphan*/  cqe; } ;
struct mlx5_ib_dev {struct umr_common umrc; } ;
struct ib_send_wr {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 int IB_WC_SUCCESS ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int ib_post_send (int /*<<< orphan*/ ,TYPE_1__*,struct ib_send_wr const**) ; 
 int /*<<< orphan*/  mlx5_ib_init_umr_context (struct mlx5_ib_umr_context*) ; 
 int /*<<< orphan*/  mlx5_ib_warn (struct mlx5_ib_dev*,char*,int) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlx5_ib_post_send_wait(struct mlx5_ib_dev *dev,
				  struct mlx5_umr_wr *umrwr)
{
	struct umr_common *umrc = &dev->umrc;
	const struct ib_send_wr *bad;
	int err;
	struct mlx5_ib_umr_context umr_context;

	mlx5_ib_init_umr_context(&umr_context);
	umrwr->wr.wr_cqe = &umr_context.cqe;

	down(&umrc->sem);
	err = ib_post_send(umrc->qp, &umrwr->wr, &bad);
	if (err) {
		mlx5_ib_warn(dev, "UMR post send failed, err %d\n", err);
	} else {
		wait_for_completion(&umr_context.done);
		if (umr_context.status != IB_WC_SUCCESS) {
			mlx5_ib_warn(dev, "reg umr failed (%u)\n",
				     umr_context.status);
			err = -EFAULT;
		}
	}
	up(&umrc->sem);
	return err;
}