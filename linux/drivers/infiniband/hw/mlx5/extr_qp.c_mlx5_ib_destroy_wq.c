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
struct mlx5_ib_rwq {int /*<<< orphan*/  core_qp; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;
struct ib_wq {int /*<<< orphan*/  pd; int /*<<< orphan*/  device; } ;
struct ib_udata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_user_rq (struct mlx5_ib_dev*,int /*<<< orphan*/ ,struct mlx5_ib_rwq*,struct ib_udata*) ; 
 int /*<<< orphan*/  kfree (struct mlx5_ib_rwq*) ; 
 int /*<<< orphan*/  mlx5_core_destroy_rq_tracked (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct mlx5_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 
 struct mlx5_ib_rwq* to_mrwq (struct ib_wq*) ; 

void mlx5_ib_destroy_wq(struct ib_wq *wq, struct ib_udata *udata)
{
	struct mlx5_ib_dev *dev = to_mdev(wq->device);
	struct mlx5_ib_rwq *rwq = to_mrwq(wq);

	mlx5_core_destroy_rq_tracked(dev->mdev, &rwq->core_qp);
	destroy_user_rq(dev, wq->pd, rwq, udata);
	kfree(rwq);
}