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
struct TYPE_4__ {struct mlx5_ib_qp* in; int /*<<< orphan*/  mdct; } ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;
struct mlx5_ib_qp {scalar_t__ state; TYPE_2__ dct; TYPE_1__ ibqp; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 scalar_t__ IB_QPS_RTR ; 
 int /*<<< orphan*/  kfree (struct mlx5_ib_qp*) ; 
 int mlx5_core_destroy_dct (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_ib_warn (struct mlx5_ib_dev*,char*,int) ; 
 struct mlx5_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx5_ib_destroy_dct(struct mlx5_ib_qp *mqp)
{
	struct mlx5_ib_dev *dev = to_mdev(mqp->ibqp.device);

	if (mqp->state == IB_QPS_RTR) {
		int err;

		err = mlx5_core_destroy_dct(dev->mdev, &mqp->dct.mdct);
		if (err) {
			mlx5_ib_warn(dev, "failed to destroy DCT %d\n", err);
			return err;
		}
	}

	kfree(mqp->dct.in);
	kfree(mqp);
	return 0;
}