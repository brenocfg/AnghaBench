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
struct TYPE_2__ {struct mlx5dr_qp* wqe_head; } ;
struct mlx5dr_qp {int /*<<< orphan*/  wq_ctrl; TYPE_1__ sq; int /*<<< orphan*/  mqp; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mlx5dr_qp*) ; 
 int /*<<< orphan*/  mlx5_core_destroy_qp (struct mlx5_core_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_wq_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dr_destroy_qp(struct mlx5_core_dev *mdev,
			  struct mlx5dr_qp *dr_qp)
{
	mlx5_core_destroy_qp(mdev, &dr_qp->mqp);
	kfree(dr_qp->sq.wqe_head);
	mlx5_wq_destroy(&dr_qp->wq_ctrl);
	kfree(dr_qp);
}